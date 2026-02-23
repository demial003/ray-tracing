#include "stuff.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

vec3 *vec3_init(double a, double b, double c) {
  vec3 *v = malloc(sizeof(vec3));
  if (v == NULL) {
    fprintf(stderr, "failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  v->x = a;
  v->y = b;
  v->z = c;
  return v;
}

vec3 *vec3_add(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  if (v3 == NULL) {
    fprintf(stderr, "failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  v3->x = v1->x + v2->x;
  v3->y = v1->y + v2->y;
  v3->z = v1->z + v2->z;
  return v3;
}

vec3 *vec3_subtract(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  if (v3 == NULL) {
    fprintf(stderr, "failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  v3->x = v1->x - v2->x;
  v3->y = v1->y - v2->y;
  v3->z = v1->z - v2->z;
  return v3;
}

vec3 *vec3_multiply(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  if (v3 == NULL) {
    fprintf(stderr, "failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  v3->x = v1->x * v2->x;
  v3->y = v1->y * v2->y;
  v3->z = v1->z * v2->z;
  return v3;
}

vec3 *vec3_scalar_multiply(vec3 *v1, double t) {
  vec3 *v3 = malloc(sizeof(vec3));
  if (v3 == NULL) {
    fprintf(stderr, "failed to allocate memory");
    exit(EXIT_FAILURE);
  }
  v3->x = v1->x * t;
  v3->y = v1->y * t;
  v3->z = v1->z * t;
  return v3;
}

vec3 *vec3_scalar_divide(vec3 *v1, double t) {
  return vec3_scalar_multiply(v1, 1.0 / t);
}

double vec3_dot(vec3 *v1, vec3 *v2) {
  return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

vec3 *vec3_cross(vec3 *v1, vec3 *v2) {
  return vec3_init(v1->y * v2->z - v1->z * v2->y, v1->z * v2->x - v1->x * v2->z,
                   v1->x * v2->y - v1->y * v2->x);
}

double vec3_length_squared(vec3 *v) {
  return v->x * v->x + v->y + v->y + v->z + v->z;
}

double vec3_length(vec3 *v) { return sqrt(vec3_length_squared(v)); }

vec3 *vec3_unit_vector(vec3 *v) {
  return vec3_scalar_divide(v, vec3_length(v));
}
void vec3_print(vec3 *v) { printf("%f %f %f\n", v->x, v->y, v->z); }

ray *ray_init(point3 *p, vec3 *v) {
  ray *r = malloc(sizeof(ray));
  r->orig = p;
  r->dir = v;
  return r;
}

point3 *ray_at(ray *r, double t) {
  return vec3_add(r->orig, vec3_scalar_multiply(r->dir, t));
}

void ray_print(ray *r) {
  printf("orig: ");
  vec3_print(r->orig);
  printf("dir: ");
  vec3_print(r->dir);
}

void ray_destroy(ray *r) { free(r); }

void write_color(color *pixel_color) {
  double r = pixel_color->x;
  double g = pixel_color->y;
  double b = pixel_color->z;

  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);

  printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
