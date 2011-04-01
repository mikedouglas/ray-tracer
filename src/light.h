#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light {
  public:
    const Point pos;
    const Color color;
    const double brightness;
    
    Light(Point pos, Color color, double brightness) : pos(pos), color(color), brightness(brightness) {}
    Ray to_light(const Point &p);
    double distance(const Point &p);
};

#endif
