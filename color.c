#include "stuff.h"
#include <stdio.h>

void write_color(color *pixel_color) {
  double r = pixel_color->x;
  double g = pixel_color->y;
  double b = pixel_color->z;

  int rbyte = (int)(255.999 * r);
  int gbyte = (int)(255.999 * g);
  int bbyte = (int)(255.999 * b);

  printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
