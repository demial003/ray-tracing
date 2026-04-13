#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include <stdbool.h>

#include "interval.h"

enum materials { LAMBERTIAN = 1, METAL = 2, DIELECTRIC = 3 };

union material_t {
  double data[5];
  struct {
    color albedo;
    int type;
    double fuzz;
    double refraction_index;
  };
};

typedef union material_t material;

union hit_record_t {
  double data[13];
  struct {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
    material mat;
  };
};

typedef union hit_record_t hit_record;

void hit_record_set_face_normal(hit_record *rec, ray r, vec3 outward_normal) {
  rec->front_face = vec3_dot(r.dir, outward_normal) < 0;
  rec->normal = rec->front_face ? outward_normal
                                : vec3_scalar_multiply(outward_normal, -1);
}

#endif
