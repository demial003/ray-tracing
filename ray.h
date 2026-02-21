#ifndef RAY_H
#define RAY_H

#include "vec3.h"
#include <stdlib.h>

typedef struct {
  vec3 *orig;
  vec3 *dir;
} ray;

ray *init_ray(vec3 *v1, vec3 *v2) {
  ray *r = malloc(sizeof(ray));
  r->orig = v1;
  r->dir = v2;
  return r;
}
vec3 *at(ray *r, double t) {
  return add_by_vec3(r->orig, multiply_vec3(r->dir, t));
}

#endif
