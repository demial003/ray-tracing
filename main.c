#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "interval.h"
#include "rtweekend.h"
#include "sphere.h"
#include "sphere_list.h"

#include "camera.h"

int main(void) {
  FILE *file;
  file = fopen("log.txt", "w");
  if (file == NULL) {
    exit(EXIT_FAILURE);
  }

  sphere_list_t world;
  int err = sl_init(&world, 10);
  if (err < 0) {
    fprintf(stderr, "failed to create sphere list world");
    exit(EXIT_FAILURE);
  }
  sphere s1 = sphere_init(vec3_init(0, 0, -1), 0.5);
  sphere s2 = sphere_init(vec3_init(0, -100.5, -1), 100);
  sl_push(&world, s1);
  sl_push(&world, s2);

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 400;
  cam.samples_per_pixel = 100;
  cam.max_depth = 50;

  render(&cam, &world, file);

  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  sl_destroy(&world);
  exit(EXIT_SUCCESS);
}
