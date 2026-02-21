#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

color *ray_color(ray *r) {
  vec3 *unit = unit_vector(r->dir);
  double a = 0.5 * unit->e2 + 1.0;
  return add_by_vec3(multiply_vec3(init_vec3(1.0, 1.0, 1.0), (1.0 - a)),
                     multiply_vec3(init_vec3(0.5, 0.7, 1.0), a));
}
int main(void) {
  FILE *file;
  // hello
  file = fopen("log.txt", "w+");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width =
      viewport_height * ((double)image_width) / image_height;
  vec3 *camera_center = init_vec3(0, 0, 0);

  vec3 *viewport_u = init_vec3(viewport_width, 0, 0);
  vec3 *viewport_v = init_vec3(0, -viewport_height, 0);

  vec3 *pixel_delta_u = divide_vec3(viewport_u, viewport_width);
  vec3 *pixel_delta_v = divide_vec3(viewport_v, viewport_height);

  vec3 *viewport_upper_left = subtract_vec3(
      camera_center, subtract_vec3(init_vec3(0, 0, focal_length),
                                   subtract_vec3(divide_vec3(viewport_u, 2),
                                                 divide_vec3(viewport_v, 2))));
  vec3 *pixel00_loc =
      multiply_by_vec3(add_vec3(viewport_upper_left, 0.5),
                       add_by_vec3(pixel_delta_u, pixel_delta_v));

  printf("P3\n%d %d\n255\n", image_width, image_height);

  for (int i = 0; i < image_height; i++) {
    for (int j = 0; j < image_width; j++) {
      fprintf(file, "\rScanlines remaining: %d\n", (image_height - j));
      vec3 *pixel_center = add_by_vec3(
          pixel00_loc, add_by_vec3(multiply_vec3(pixel_delta_u, i),
                                   multiply_vec3(pixel_delta_v, j)));
      vec3 *ray_direction = subtract_vec3(pixel_center, camera_center);
      ray *r = init_ray(camera_center, ray_direction);
      color *pixel_color = init_vec3(0, 0, 0);
      write_color(pixel_color);
    }
  }
  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  exit(EXIT_SUCCESS);
}
