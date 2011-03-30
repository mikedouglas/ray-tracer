#include <cmath>
#include "sphere.h"
#include "vec3.h"

Vector Sphere::normal(const Point &point) {
    Vector nrm(point.x - pos.x, point.y - pos.y, point.z - pos.z);
    return nrm/r;
}

double Sphere::intersect(const Ray &ray) {
    double xadj = ray.origin.x - pos.x;
    double yadj = ray.origin.y - pos.y;
    double zadj = ray.origin.z - pos.z;
    
    double b = xadj*ray.dir.x + yadj*ray.dir.y + zadj*ray.dir.z;
    double t = b*b - xadj*xadj - yadj*yadj - zadj*zadj + r*r;
    
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