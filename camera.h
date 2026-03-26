#ifndef CAMERA_H
#define CAMERA_H

#include "rtweekend.h"

#include "hittable.h"

union camera_t {
  double data[16];
  struct {
    double aspect_ratio;
    int image_width;
    int image_height;
    point3 center;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
  };
};

typedef union camera_t camera;

color ray_color(ray r, sphere_list_t *world) {
  hit_record rec;
  if (sphere_list_hit(world, r, interval_init(0, infinity), &rec)) {
    color c = vec3_init(1, 1, 1);
    return vec3_scalar_multiply(vec3_add(rec.normal, c), 0.5);
  }

  vec3 unit = vec3_unit_vector(r.dir);
  double a = 0.5 * (unit.y + 1.0);
  vec3 comp1 = vec3_scalar_multiply(vec3_init(1.0, 1.0, 1.0), 1.0 - a);
  vec3 comp2 = vec3_scalar_multiply(vec3_init(0.5, 0.7, 1.0), a);
  return vec3_add(comp1, comp2);
}

void initialize(camera *cam) {
  cam->image_height = (int)(cam->image_width / cam->aspect_ratio);
  //  cam->image_height = (cam->image_height < 1) ? 1 : cam->image_height;

  cam->center = vec3_init(0, 0, 0);

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)cam->image_width) / cam->image_height;
  cam->center = vec3_init(0, 0, 0);

  vec3 viewport_u = vec3_init(viewport_width, 0, 0);
  vec3 viewport_v = vec3_init(0, -viewport_height, 0);

  cam->pixel_delta_u = vec3_scalar_divide(viewport_u, (double)cam->image_width);
  cam->pixel_delta_v =
      vec3_scalar_divide(viewport_v, (double)cam->image_height);

  point3 viewport_uppper_left = vec3_subtract(
      cam->center, vec3_add(vec3_init(0, 0, focal_length),
                            vec3_add(vec3_scalar_divide(viewport_u, 2),
                                     vec3_scalar_divide(viewport_v, 2))));
  cam->pixel00_loc =
      vec3_add(viewport_uppper_left,
               vec3_scalar_multiply(
                   vec3_add(cam->pixel_delta_u, cam->pixel_delta_v), 0.5));
}

void render(camera *cam, sphere_list_t *world, FILE *file) {
  initialize(cam);

  printf("P3\n%d %d\n255\n", cam->image_width, cam->image_height);

  for (int j = 0; j < cam->image_height; j++) {
    fprintf(file, "\rScanlines remaining: %d\n", cam->image_height - j);
    for (int i = 0; i < cam->image_width; i++) {
      vec3 pixel_center = vec3_add(
          cam->pixel00_loc,
          vec3_add(vec3_scalar_multiply(cam->pixel_delta_u, (double)i),
                   vec3_scalar_multiply(cam->pixel_delta_v, (double)j)));
      vec3 ray_direction = vec3_subtract(pixel_center, cam->center);
      ray r = ray_init(cam->center, ray_direction);

      color pixel_color = ray_color(r, world);
      write_color(pixel_color);
    }
  }
}

#endif
