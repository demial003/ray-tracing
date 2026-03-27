#ifndef RTWEEKEND_H
#define RTWEEKEND_H

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

const double infinity = INFINITY;
const double pi = 3.1415926535897932385;

double degrees_to_radians(double degrees) { return degrees * pi / 180.0; }

double rand_double() { return rand() / (RAND_MAX + 1.0); }

double random_double(double min, double max) {
  return min + (max - min) * rand_double();
}

#include "vec3.h"

#include "color.h"
#include "ray.h"

#endif
