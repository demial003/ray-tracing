#ifndef SPHERE_LIST_H
#define SPHERE_LIST_H

#include "sphere.h"
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE 4096

typedef struct {
  sphere *data;
  unsigned cap;
  unsigned len;
} sphere_list_t;

int sl_init(sphere_list_t *s, unsigned capacity) {
  assert(capacity > 0);
  s->data = malloc(capacity * sizeof(sphere *));
  if (s->data == NULL) {
    return -1;
  }
  s->cap = capacity;
  s->len = 0;

  return 0;
}

int sl_length(sphere_list_t *s) { return s->len; }

void sl_destroy(sphere_list_t *s) {
  free(s->data);
  s->data = NULL;
  s->len = 0;
  s->cap = 0;
}

int sl_push(sphere_list_t *s, sphere item) {
  if (s->len == s->cap) {
    s->cap *= 2;
    sphere *s2 = realloc(s->data, s->cap * sizeof(sphere *));
    if (s2 == NULL) {
      return -1;
    }
    s->data = s2;
  }

  s->data[s->len] = item;
  s->len++;

  return -0;
}

bool sphere_list_hit(sphere_list_t *s, ray r, interval ray_t, hit_record *rec) {
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = ray_t.max;

  for (int i = 0; i < s->len; i++) {
    if (sphere_hit(s->data[i], r, interval_init(ray_t.min, closest_so_far),
                   &temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.t;
      *rec = temp_rec;
    }
  }

  return hit_anything;
}

#endif
