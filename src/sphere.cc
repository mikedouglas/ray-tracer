#include <cmath>
#include "shape.h"
#include "sphere.h"
#include "surface.h"
#include "vec3.h"

Vector Sphere::normal(const Point &point) {
  Vector nrm(point.x - pos.x, point.y - pos.y, point.z - pos.z);
  return nrm/r;
}

Surface *Sphere::getSurface() {
  return surface;
}

double Sphere::intersect(const Ray &ray) {
  Vector adj = ray.origin - pos;
  
  double b = adj.x*ray.dir.x + adj.y*ray.dir.y + adj.z*ray.dir.z;
  double t = b*b - adj.x*adj.x - adj.y*adj.y - adj.z*adj.z + r*r;
    
  if (t < 0)
    return 0;
  double s = -b - sqrt(t);
  if (s > 0)
    return s;
  else {
    s = -b + sqrt(t);
    if (s > 0)
      return s;
    return 0;
  }
}
