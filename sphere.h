#ifndef SPHERE_H
#define SPHERE_H

#include "shape.h"
#include "vec3.h"

class Sphere : public Shape {
public:
    const double r;
    const Point pos;
    const Surface *surface;

    Sphere(Surface *surface, double r, double x, double y, double z)
      : surface(surface), r(r), pos(Point(x,y,z)) {}
    
    virtual double intersect(const Ray &ray);
    virtual Vector normal(const Point &point);
};

#endif