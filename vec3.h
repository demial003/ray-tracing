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

vec3 vec3_rand() {
  return vec3_init(rand_double(), rand_double(), rand_double());
}

vec3 vec3_random(double min, double max) {
  return vec3_init(random_double(min, max), random_double(min, max),
                   random_double(min, max));
}

vec3 vec3_random_unit_vector() {
  while (1) {
    vec3 p = vec3_random(-1, 1);
    double lensq = vec3_length_squared(p);
    if (1e-160 < lensq && lensq <= 1) {
      return vec3_scalar_divide(p, sqrt(lensq));
    }
  }
}

vec3 vec3_random_on_hemisphere(vec3 normal) {
  vec3 on_unit_sphere = vec3_random_unit_vector();
  if (vec3_dot(normal, on_unit_sphere) > 0.0) {
    return on_unit_sphere;
  } else {
    return vec3_scalar_multiply(on_unit_sphere, -1);
  }
}

bool vec3_near_zero(vec3 v) {
  double s = 1e-8;
  return abs(v.x < s) && abs(v.y < s) && abs(v.z < s);
}

vec3 vec3_reflect(vec3 v, vec3 n) {
  return vec3_subtract(v, vec3_scalar_multiply(n, vec3_dot(v, n) * 2));
}

vec3 vec3_refract(vec3 uv, vec3 n, double etai_over_etat) {
  double cos_theta = fmin(vec3_dot(vec3_scalar_multiply(uv, -1), n), 1.0);
  vec3 r_out_perp = vec3_scalar_multiply(
      vec3_add(uv, vec3_scalar_multiply(n, cos_theta)), etai_over_etat);
  vec3 r_out_parallel = vec3_scalar_multiply(
      n, -sqrt(fabs(1.0 - vec3_length_squared(r_out_perp))));
  return vec3_add(r_out_perp, r_out_parallel);
}

void vec3_print(vec3 v) { printf("%f %f %f\n", v.x, v.y, v.z); }

#endif
