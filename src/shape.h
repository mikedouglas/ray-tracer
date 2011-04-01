#ifndef SHAPE_H
#define SHAPE_H

#include "vec3.h"
#include "surface.h"

class Shape {
public:
    virtual double intersect(const Ray &ray) = 0;
    virtual Vector normal(const Point &point) = 0;
    virtual Surface *getSurface() = 0;
};

#endif
