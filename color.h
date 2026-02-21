#ifndef COLOR_H
#define COLOR_H

#include "vec3.h"

typedef vec3 color;

void write_color(color *pixel_color) {
  double r = pixel_color->e0;
  double g = pixel_color->e1;
  double b = pixel_color->e2;

  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);

  printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
#endif
