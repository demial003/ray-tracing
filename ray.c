#include "vec3.c"

typedef struct {
  point3 *orig;
  vec3 *dir;
} ray;

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
