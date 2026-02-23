#include "vec3.c"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

color *ray_color(ray *r) {
  vec3 *unit = vec3_unit_vector(r->dir);
  double a = 0.5 * (unit->y + 1.0);
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
  double viewport_width =
      viewport_height * ((double)image_width) / image_height;
  point3 *camera_center = vec3_init(0, 0, 0);

  vec3 *viewport_u = vec3_init(viewport_width, 0, 0);
  vec3 *viewport_v = vec3_init(0, -viewport_height, 0);
  ;

  vec3 *pixel_data_u = vec3_scalar_divide(viewport_u, image_width);
  vec3 *pixel_data_v = vec3_scalar_divide(viewport_v, image_height);

  point3 *viewport_uppper_left =
      vec3_subtract(vec3_subtract(camera_center, vec3_init(0, 0, focal_length)),
                    vec3_subtract(vec3_scalar_divide(viewport_u, 2.0),
                                  vec3_scalar_divide(viewport_v, 2.0)));
  point3 *pixel00_loc =
      vec3_add(viewport_uppper_left,
               vec3_scalar_multiply(vec3_add(pixel_data_u, pixel_data_v), 0.5));

  printf("P3\n%d %d \n255\n", image_width, image_height);
  for (int j = 0; j < image_height; j++) {
    fprintf(file, "\rScanlines remaining: ", image_height - j);
    for (int i = 0; i < image_width; i++) {
      vec3 *pixel_center = vec3_add(
          pixel00_loc, vec3_add(vec3_scalar_multiply(pixel_data_u, i),
                                vec3_scalar_multiply(pixel_data_v, j)));
      vec3 *ray_direction = vec3_subtract(pixel_center, camera_center);
      ray *r = ray_init(camera_center, ray_direction);
      color *pixel_color = ray_color(r);
      write_color(pixel_color);
    }
  }

  free(viewport_u);
  free(viewport_v);
  free(pixel_data_u);
  free(pixel_data_v);
  free(viewport_uppper_left);

  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  exit(EXIT_SUCCESS);
}
