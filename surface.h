#ifndef SURFACE_H
#define SURFACE_H

#include "vec3.h"

class Surface {
public:
    const Color color;
    const double s_coef; // specular coefficient
    const double refl; // reflection [0,1]
    const double transp; // transparency [0,1]
    
    Surface(Color color, double s_coef, double refl, double transp) : color(color), s_coef(s_coef), refl(refl), transp(transp) {}
};

#endif