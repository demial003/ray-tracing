typedef struct {
  double x;
  double y;
  double z;
} vec3;

typedef vec3 color;
typedef vec3 point3;

typedef struct {
  point3 *orig;
  vec3 *dir;
} ray;
