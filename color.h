#ifndef COLOR_H
#define COLOR_H
#include "vec3.h"
#include <stdio.h>

void write_color(color pixel_color) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  int rbyte = (255.999 * r);
  int gbyte = (255.999 * g);
  int bbyte = (255.999 * b);

  printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
#endif
