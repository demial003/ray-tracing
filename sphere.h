#ifndef SPHERE_H
#define SPHERE_H

#include "hittable.h"
#include <stdbool.h>

union sphere_t {
  double data[4];
  struct {
    point3 center;
    double radius;
  };
};

typedef union sphere_t sphere;

sphere sphere_init(point3 center, double radius) {
  sphere s;
  if (radius > 0) {
    s.radius = radius;
  } else {
    s.radius = 0;
  }
  s.center = center;
  return s;
}

bool sphere_hit(sphere s, ray r, interval ray_t, hit_record *rec) {
  vec3 oc = vec3_subtract(s.center, r.orig);
  double a = vec3_dot(r.dir, r.dir);
  double h = vec3_dot(r.dir, oc);
  double c = vec3_dot(oc, oc) - s.radius * s.radius;

  double discriminant = h * h - a * c;

  if (discriminant < 0) {
    return false;
  }

  double sqrtd = sqrt(discriminant);
  double root = (h - sqrtd) / a;
  if (!interval_surrounds(ray_t, root)) {
    root = (h + sqrtd) / a;
    if (!interval_surrounds(ray_t, root)) {
      return false;
    }
  }

  rec->t = root;
  rec->p = ray_at(r, rec->t);
  vec3 outward_normal =
      vec3_scalar_divide(vec3_subtract(rec->p, s.center), s.radius);
  hit_record_set_face_normal(rec, r, outward_normal);
  return true;
}

#endif
