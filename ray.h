#ifndef RAY_H
#define RAY_H

#include "vec3.h"

ray ray_init(point3 p, vec3 v) {
  ray r = {.orig = p, .dir = v};
  return r;
}

point3 ray_at(ray r, double t) {
  return vec3_add(r.orig, vec3_scalar_multiply(r.dir, t));
}

#endif
