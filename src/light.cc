#include "light.h"

Ray Light::to_light(const Point &p) {
  return Ray(p, (pos - p).normalize());
}

double Light::distance(const Point &p) {
  Vector v = pos - p;
  return v.x*v.x + v.y*v.y + v.z*v.z;
}
