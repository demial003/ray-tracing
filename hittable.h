#ifndef HITTABLE_H
#define HITTABLE_H

#include "vec3.h"
#include <stdbool.h>

union hit_record_t {
  double data[10];
  struct {
    point3 p;
    vec3 normal;
    double t;
    bool front_face;
  };
};

typedef union hit_record_t hit_record;

void hit_record_set_face_normal(hit_record *rec, ray r, vec3 outward_normal) {
  rec->front_face = vec3_dot(r.dir, outward_normal) < 0;
  rec->normal = rec->front_face ? outward_normal
                                : vec3_scalar_multiply(outward_normal, -1);
}

#endif
