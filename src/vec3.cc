#include <iostream>
#include <cmath>
#include "vec3.h"

double dot(const Vec3 &a, const Vec3 &b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 cross(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.y*b.z - a.z*b.y, a.z*b.x - a.x*b.z, a.x*b.y - a.y*b.x);
}

std::ostream& operator<<(std::ostream& out, const Vec3& v) {
  return out << "Vector(" << v.x << "," << v.y << "," << v.z << ")";
}

Vec3 operator+(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x+b.x, a.y+b.y, a.z+b.z);
}

Vec3 operator-(const Vec3 &a, const Vec3 &b) {
    return Vec3(a.x-b.x, a.y-b.y, a.z-b.z);
}

Vec3 operator*(double a, const Vec3 &b) {
    return Vec3(a*b.x, a*b.y, a*b.z);
}

Vec3 operator/(const Vec3 &a, double b) {
    return Vec3(a.x/b, a.y/b, a.z/b);
}

bool operator==(const Vec3 &a, const Vec3 &b) {
    return (a.x == b.x) && (a.y == b.y) && (a.z == b.z);
}

bool operator!=(const Vec3 &a, const Vec3 &b) {
    return !(a == b);
}

Vec3 Vec3::normalize() {
    double d = sqrt(x*x + y*y + z*z);
    return Vec3(x/d, y/d, z/d);
}
