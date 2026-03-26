#ifndef COLOR_H
#define COLOR_H

#include "interval.h"
#include "vec3.h"

void write_color(color pixel_color) {
  double r = pixel_color.x;
  double g = pixel_color.y;
  double b = pixel_color.z;

  interval intensity = interval_init(0.000, 0.999);
  int rbyte = (256 * interval_clamp(intensity, r));
  int gbyte = (256 * interval_clamp(intensity, g));
  int bbyte = (256 * interval_clamp(intensity, b));

  printf("%d %d %d\n", rbyte, gbyte, bbyte);
}
#endif
