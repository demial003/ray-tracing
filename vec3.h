#ifndef VEC3_H
#define VEC3_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

union vec3_t {
  double elements[3];
  struct {
    double x;
    double y;
    double z;
  };
};

typedef union vec3_t vec3;
typedef union vec3_t color;
typedef union vec3_t point3;

union ray_t {
  vec3 elements[6];
  struct {
    vec3 orig;
    vec3 dir;
  };
};

typedef union ray_t ray;

vec3 vec3_init(double a, double b, double c) {
  vec3 v = {.x = a, .y = b, .z = c};
  return v;
}

vec3 vec3_add(vec3 v1, vec3 v2) {
  return vec3_init(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
}

vec3 vec3_subtract(vec3 v1, vec3 v2) {

  return vec3_init(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

vec3 vec3_multiply(vec3 v1, vec3 v2) {
  return vec3_init(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

vec3 vec3_scalar_multiply(vec3 v1, double t) {

  return vec3_init(v1.x * t, v1.y * t, v1.z * t);
}

vec3 vec3_scalar_divide(vec3 v1, double t) {
  return vec3_scalar_multiply(v1, 1.0 / t);
}

double vec3_dot(vec3 v1, vec3 v2) {
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

vec3 vec3_cross(vec3 v1, vec3 v2) {
  return vec3_init(v1.y * v2.z - v1.z * v2.y, v1.x * v2.z - v1.z * v2.x,
                   v1.x * v2.y - v2.y * v1.x);
}

double vec3_length_squared(vec3 v) { return vec3_dot(v, v); }

double vec3_length(vec3 v) { return sqrt(vec3_length_squared(v)); }

vec3 vec3_unit_vector(vec3 v) { return vec3_scalar_divide(v, vec3_length(v)); }
void vec3_print(vec3 v) { printf("%f %f %f\n", v.x, v.y, v.z); }

#endif
