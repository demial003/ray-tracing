#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rtweekend.h"

#include "hittable.h"
#include "material.h"
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

  material material_ground = {.albedo = vec3_init(0.0, 0.2, 0.0),
                              .type = LAMBERTIAN};
  material material_center = {.albedo = vec3_init(0.7, 0.3, 0.9),
                              .type = LAMBERTIAN};
  material material_left = {.type = DIELECTRIC, .refraction_index = 1.50};
  material material_bubble = {.type = DIELECTRIC,
                              .refraction_index = 1.00 / 1.50};
  material material_right = {
      .albedo = vec3_init(0.3, 0.3, 0.7), .type = METAL, .fuzz = 1.0};

  sphere s1 = sphere_init(vec3_init(0.0, -100.5, -1.0), 100.0, material_ground);
  sphere s2 = sphere_init(vec3_init(0.0, 0.0, -1.2), 0.5, material_center);
  sphere s3 = sphere_init(vec3_init(-1.0, 0.0, -1.0), 0.5, material_left);
  sphere s4 = sphere_init(vec3_init(1.0, 0.0, -1.0), 0.5, material_right);
  sphere s5 = sphere_init(vec3_init(-1.0, 0.0, -1.0), 0.4, material_bubble);

  if (sl_push(&world, s1) < 0) {
    fprintf(stderr, "failed to push sphere into list");
    exit(EXIT_FAILURE);
  }

  if (sl_push(&world, s2) < 0) {
    fprintf(stderr, "failed to push sphere into list");
    exit(EXIT_FAILURE);
  }
  if (sl_push(&world, s3) < 0) {
    fprintf(stderr, "failed to push sphere into list");
    exit(EXIT_FAILURE);
  }
  if (sl_push(&world, s4) < 0) {
    fprintf(stderr, "failed to push sphere into list");
    exit(EXIT_FAILURE);
  }
  if (sl_push(&world, s5) < 0) {
    fprintf(stderr, "failed to push sphere into list");
    exit(EXIT_FAILURE);
  }

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
