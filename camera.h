#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "hittable.h"
#include "material.h"

union camera_t {
  double data[40];
  struct {
    double aspect_ratio;
    int image_width;
    int image_height;
    int samples_per_pixel;
    double pixel_samples_scale;
    int max_depth;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    double vfov;
    point3 lookfrom;
    point3 lookat;
    vec3 vup;
    double defocus_angle;
    double focus_dist;
    vec3 defocus_disk_u;
    vec3 defocus_disk_v;
  };
};

typedef union camera_t camera;

color ray_color(ray r, int depth, sphere_list_t *world) {
  if (depth <= 0) {
    return vec3_init(0, 0, 0);
  }
  hit_record rec;
  if (sphere_list_hit(world, r, interval_init(0.001, infinity), &rec)) {
    ray scattered;
    color attenuation;
    if (material_scatter(r, rec, &attenuation, &scattered)) {
      return vec3_multiply(ray_color(scattered, depth - 1, world), attenuation);
    }
    return vec3_init(0, 0, 0);
  }

  vec3 unit = vec3_unit_vector(r.dir);
  double a = 0.5 * (unit.y + 1.0);
  vec3 comp1 = vec3_scalar_multiply(vec3_init(1.0, 1.0, 1.0), 1.0 - a);
  vec3 comp2 = vec3_scalar_multiply(vec3_init(0.5, 0.7, 1.0), a);
  return vec3_add(comp1, comp2);
}

vec3 sample_square() {
  return vec3_init(rand_double() - 0.5, rand_double() - 0.5, 0);
}

point3 defocus_disk_sample(camera *cam) {
  vec3 p = vec3_random_in_unit_disk();
  vec3 comp_u = vec3_scalar_multiply(cam->defocus_disk_u, p.x);
  vec3 comp_v = vec3_scalar_multiply(cam->defocus_disk_v, p.y);
  return vec3_add(cam->center, vec3_add(comp_u, comp_v));
}
ray get_ray(camera *cam, int i, int j) {
  vec3 offset = sample_square();
  vec3 pixel_sample = vec3_add(
      cam->pixel00_loc,
      vec3_add(vec3_scalar_multiply(cam->pixel_delta_u, i + offset.x),
               vec3_scalar_multiply(cam->pixel_delta_v, j + offset.y)));
  point3 ray_origin =
      (cam->defocus_angle <= 0) ? cam->center : defocus_disk_sample(cam);
  vec3 ray_direction = vec3_subtract(pixel_sample, ray_origin);
  ray r = ray_init(ray_origin, ray_direction);

  return r;
}

void initialize(camera *cam) {
  cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
  cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;
  cam->pixel_samples_scale = 1.0 / cam->samples_per_pixel;

  cam->center = cam->lookfrom;

  double theta = degrees_to_radians(cam->vfov);
  double h = tan(theta / 2.0);
  double viewport_height = 2.0 * h * cam->focus_dist;
  double viewport_width =
      viewport_height * ((double)cam->image_width / (double)cam->image_height);

  vec3 w = vec3_unit_vector(vec3_subtract(cam->lookfrom, cam->lookat));
  vec3 u = vec3_unit_vector(vec3_cross(cam->vup, w));
  vec3 v = vec3_cross(w, u);

  vec3 viewport_u = vec3_scalar_multiply(u, viewport_width);
  vec3 viewport_v =
      vec3_scalar_multiply(vec3_scalar_multiply(v, -1.0), viewport_height);

  cam->pixel_delta_u = vec3_scalar_divide(viewport_u, (double)cam->image_width);
  cam->pixel_delta_v =
      vec3_scalar_divide(viewport_v, (double)cam->image_height);

  vec3 half_u = vec3_scalar_divide(viewport_u, 2.0);
  vec3 half_v = vec3_scalar_divide(viewport_v, 2.0);
  vec3 look_direction = vec3_scalar_multiply(w, cam->focus_dist);

  point3 viewport_upper_left = vec3_subtract(
      vec3_subtract(vec3_subtract(cam->center, look_direction), half_u),
      half_v);

  cam->pixel00_loc =
      vec3_add(viewport_upper_left,
               vec3_scalar_multiply(
                   vec3_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));

  double defocus_radius =
      cam->focus_dist * tan(degrees_to_radians(cam->defocus_angle / 2));
  cam->defocus_disk_u = vec3_scalar_multiply(u, defocus_radius);
  cam->defocus_disk_v = vec3_scalar_multiply(v, defocus_radius);
}

void render(camera *cam, sphere_list_t *world, FILE *file) {
  initialize(cam);

  printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);
  for (int j = 0; j < cam->image_height; j++) {
    fprintf(file, "\rScanlines remaining: %d\n", cam->image_height - j);
    for (int i = 0; i < cam->image_width; i++) {
      color pixel_color = vec3_init(0.0, 0.0, 0.0);
      for (int sample = 0; sample < cam->samples_per_pixel; sample++) {
        ray r = get_ray(cam, i, j);
        pixel_color =
            vec3_add(pixel_color, ray_color(r, cam->max_depth, world));
      }
      write_color(vec3_scalar_multiply(pixel_color, cam->pixel_samples_scale));
    }
  }
}

#endif
