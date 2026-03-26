#ifndef INTERVAL_H
#define INTERVAL_H

typedef struct {
  double data[2];
  double min, max;
} interval;

interval interval_init(double min, double max) {
  interval a;
  a.min = min;
  a.max = max;
  return a;
}

double interval_size(interval h) { return h.max - h.min; }

bool interval_contains(interval h, double x) {
  return h.min <= x && h.max <= x;
}

bool interval_surrounds(interval h, double x) { return h.min < x && h.max > x; }

#endif
