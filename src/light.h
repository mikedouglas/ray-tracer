#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"

class Light {
    Point pos;
    Color color;
    double bright;
    
    Light(Point pos, Color color, double bright) : pos(pos), color(color), bright(bright) {}
};

#endif