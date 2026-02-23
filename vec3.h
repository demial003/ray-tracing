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

typedef struct {
  vec3 orig;
  vec3 dir;
} ray;

vec3 vec3_init(double a, double b, double c) {
  vec3 v = {.x = a, .y = b, .z = c};
  return v;
}

vec3 vec3_add(vec3 v1, vec3 v2) {}

vec3 vec3_subtract(vec3 v1, vec3 v2) {}

vec3 vec3_multiply(vec3 v1, vec3 v2) {}

vec3 vec3_scalar_multiply(vec3 v1, double t) {}

vec3 vec3_scalar_divide(vec3 v1, double t) {}

double vec3_dot(vec3 v1, vec3 v2) {}

vec3 vec3_cross(vec3 v1, vec3 v2) {}

double vec3_length_squared(vec3 v) {}

double vec3_length(vec3 v) {}

vec3 vec3_unit_vector(vec3 v) {}
void vec3_print(vec3 v) {}
