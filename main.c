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
  int err = sl_init(&world, 1000);
  if (err < 0) {
    fprintf(stderr, "failed to create sphere list world");
    exit(EXIT_FAILURE);
  }

  material ground_material = {.albedo = vec3_init(0.5, 0.5, 0.5),
                              .type = LAMBERTIAN};
  if (sl_push(&world,
              sphere_init(vec3_init(0, -1000, 0), 1000, ground_material)) < 0) {
    fprintf(stderr, "failed to push sphere onto list");
    exit(EXIT_FAILURE);
  }

  for (int i = -11; i < 11; i++) {
    for (int j = -11; j < 11; j++) {
      double choose_mat = rand_double();
      point3 center =
          vec3_init(i + 0.9 * rand_double(), 0.2, j + 0.9 * rand_double());
      if (vec3_length(vec3_subtract(center, vec3_init(4, 0.2, 0))) > 0.9) {
        material sphere_material;

        if (choose_mat < 0.8) {
          color albedo = vec3_multiply(vec3_rand(), vec3_rand());
          sphere_material.albedo = albedo;
          sphere_material.type = LAMBERTIAN;
          if (sl_push(&world, sphere_init(center, 0.2, sphere_material)) < 0) {
            fprintf(stderr, "failed to push sphere into list");
            exit(EXIT_FAILURE);
          }
        } else if (choose_mat < 0.95) {
          color albedo = vec3_random(0.5, 1);
          double fuzz = random_double(0, 0.5);
          sphere_material.albedo = albedo;
          sphere_material.type = METAL;
          if (sl_push(&world, sphere_init(center, 0.2, sphere_material)) < 0) {
            fprintf(stderr, "failed to push sphere into list");
            exit(EXIT_FAILURE);
          }
        } else {
          sphere_material.type = DIELECTRIC;
          sphere_material.refraction_index = 1.5;
          if (sl_push(&world, sphere_init(center, 0.2, sphere_material)) < 0) {
            fprintf(stderr, "failed to push sphere into list");
            exit(EXIT_FAILURE);
          }
        }
      }
    }
  }

  material mat1 = {.type = DIELECTRIC, .refraction_index = 1.5};
  sl_push(&world, sphere_init(vec3_init(0, 1, 0), 1.0, mat1));

  material mat2 = {.albedo = vec3_init(0.4, 0.2, 0.1), .type = LAMBERTIAN};
  sl_push(&world, sphere_init(vec3_init(-4, 1, 0), 1.0, mat2));

  material mat3 = {
      .albedo = vec3_init(0.7, 0.6, 0.5), .type = METAL, .fuzz = 0.0};
  sl_push(&world, sphere_init(vec3_init(4, 1, 0), 1.0, mat3));

  camera cam;

  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1200;
  cam.samples_per_pixel = 10;
  cam.max_depth = 50;

  cam.vfov = 20;
  cam.lookfrom = vec3_init(13, 2, 3);
  cam.lookat = vec3_init(0, 0, 0);
  cam.vup = vec3_init(0, 1, 0);

  cam.defocus_angle = 0.6;
  cam.focus_dist = 10.0;

  render(&cam, &world, file);

  fprintf(file, "\rDone.						"
                "		\n");
  fclose(file);
  sl_destroy(&world);
  exit(EXIT_SUCCESS);
}
