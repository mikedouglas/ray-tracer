#include "light.h"

Ray Light::to_light(const Point &p) {
  return Ray(p, (pos - p).normalize());
}
