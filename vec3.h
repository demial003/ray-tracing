#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double x;
  double y;
  double z;
} vec3;

vec3 *init_vec3(double a, double b, double c) {
  vec3 *v = malloc(sizeof(vec3));
  v->x = a;
  v->y = b;
  v->z = c;
  return v;
}

void print_vec3(vec3 *v) { printf("%f %f %f\n", v->x, v->y, v->z); }

#endif
