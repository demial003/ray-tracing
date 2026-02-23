#include "color.h"
#include "ray.h"
#include "vec3.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

color ray_color(ray *r) {
  vec3 unit = vec3_unit_vector(r->dir);
  double a = 0.5(unit->y + 1.0);
  return vec3_add(vec3_scalar_multiply(vec3_init(1.0, 1.0, 1.0), 1.0 - a),
                  vec3_scalar_multiply(vec3_init(0.5, 0.7, 1.0), a));
}

int main(void) {
  FILE *file;
  // hello
  file = fopen("log.txt", "w");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  double aspect_ratio = 16.0 / 9.0;
  int image_width = 400;
  int image_height = (int)(image_width / aspect_ratio);
  image_height = (image_height < 1) ? 1 : image_height;

  double focal_length = 1.0;
  double viewport_height = 2.0;
  double viewport_width = viewport_height((double)image_width) / image_height;
  point3 camera_center = vec3_init(0, 0, 0);

  vec3 viewport_u = vec3_init(viewport_width, 0, 0);
  vec3 viewport_v = vec3_init(0, -viewport_height, 0);
  ;

  printf("viewport u: ");
  vec3_print(viewport_u);

  printf("viewport v: ");
  vec3_print(viewport_v);

  vec3 pixel_delta_u = vec3_scalar_divide(viewport_u, (double)image_width);
  vec3 pixel_delta_v = vec3_scalar_divide(viewport_v, (double)image_height);

  printf("pixel_delta_u u: ");
  vec3_print(pixel_delta_u);

  printf("pixel_delta_v v: ");
  vec3_print(pixel_delta_v);

  point3 viewport_uppper_left =
      vec3_subtract(vec3_subtract(camera_center, vec3_init(0, 0, focal_length)),
                    vec3_subtract(vec3_scalar_divide(viewport_u, 2.0),
                                  vec3_scalar_divide(viewport_v, 2.0)));

  printf("viewport_uppper_left: ");
  vec3_print(viewport_uppper_left);

  point3 pixel00_loc = vec3_add(
      viewport_uppper_left,
      vec3_scalar_multiply(vec3_add(pixel_delta_u, pixel_delta_v), 0.5));
  printf("P3\n%d %d \n255\n", image_width, image_height);
  printf("pixel00_loc: ");
  vec3_print(pixel00_loc);

  for (int j = 0; j < image_height; j++) {
    int j, i = 0;
    fprintf(file, "\rScanlines remaining: ", image_height - j);
    for (int i = 0; i < image_width; i++) {
      vec3 pixel_center =
          vec3_add(pixel00_loc,
                   vec3_add(vec3_scalar_multiply(pixel_delta_u, (double)i),
                            vec3_scalar_multiply(pixel_delta_v, (double)j)));
      vec3 ray_direction = vec3_subtract(pixel_center, camera_center);
      ray r = ray_init(camera_center, ray_direction);
      color pixel_color = ray_color(r);
      write_color(pixel_color);
      // huhhh
    }
  }

  free(viewport_u);
  free(viewport_v);
  free(pixel_delta_u);
  free(pixel_delta_v);
  // free(viewport_uppper_left);

  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  exit(EXIT_SUCCESS);
}
