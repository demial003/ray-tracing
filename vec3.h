#ifndef VEC_H
#define VEC_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
  double e0;
  double e1;
  double e2;
} vec3;

vec3 *init_vec3(double x, double y, double z) {
  vec3 *v = malloc(sizeof(vec3));
  v->e0 = x;
  v->e1 = y;
  v->e2 = z;
  return v;
}

void negate_vec3(vec3 *v) {
  v->e0 *= -1;
  v->e1 *= -1;
  v->e2 *= -1;
}

void concat_vec3(vec3 *v1, vec3 *v2) {
  v1->e0 += v2->e0;
  v1->e1 += v2->e1;
  v1->e2 += v2->e2;
}

void scale_up_vec3(vec3 *v, int t) {
  v->e0 *= t;
  v->e1 *= t;
  v->e2 *= t;
}

void scale_down_vec3(vec3 *v, int t) { scale_up_vec3(v, 1 / t); }

double length_squared(vec3 *v) {
  return (v->e0 *= v->e0) + (v->e1 *= v->e1) + (v->e2 *= v->e2);
}

double length(vec3 *v) { return sqrt(length_squared(v)); }

void print_vec3(vec3 *v) { printf("%f %f %f\n", v->e0, v->e1, v->e2); }

vec3 *add_vec3(vec3 *v1, double t) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 + t;
  v3->e1 = v1->e1 + t;
  v3->e2 = v1->e2 + t;
  return v3;
}

vec3 *add_by_vec3(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 + v2->e0;
  v3->e1 = v1->e1 + v2->e1;
  v3->e2 = v1->e2 + v2->e2;
  return v3;
}

vec3 *subtract_vec3(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 - v2->e0;
  v3->e1 = v1->e1 - v2->e1;
  v3->e2 = v1->e2 - v2->e2;
  return v3;
}

vec3 *multiply_vec3(vec3 *v1, double t) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 * t;
  v3->e1 = v1->e1 * t;
  v3->e2 = v1->e2 * t;
  return v3;
}

vec3 *multiply_by_vec3(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 * v2->e0;
  v3->e1 = v1->e1 * v2->e1;
  v3->e2 = v1->e2 * v2->e2;
  return v3;
}

vec3 *divide_by_vec3(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 / v2->e0;
  v3->e1 = v1->e1 / v2->e1;
  v3->e2 = v1->e2 / v2->e2;
  return v3;
}

vec3 *divide_vec3(vec3 *v1, double t) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = v1->e0 / t;
  v3->e1 = v1->e1 / t;
  v3->e2 = v1->e2 / t;
  return v3;
}

double dot_vec3(vec3 *v1, vec3 *v2) {
  return (v1->e0 * v2->e0) + (v1->e1 * v2->e1) + (v1->e2 * v2->e2);
}

vec3 *cross_vec3(vec3 *v1, vec3 *v2) {
  vec3 *v3 = malloc(sizeof(vec3));
  v3->e0 = (v1->e1 * v2->e2 - v1->e2 * v1->e1);
  v3->e1 = (v1->e2 * v2->e0 - v1->e0 * v1->e2);
  v3->e0 = (v1->e0 * v2->e1 - v1->e1 * v1->e0);
  return v3;
}

vec3 *unit_vector(vec3 *v) { return divide_vec3(v, length(v)); }
#endif
