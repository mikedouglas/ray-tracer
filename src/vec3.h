#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
  Vec3() : x(0), y(0), z(0) {}
  Vec3(double x2, double y2, double z2) : x(x2), y(y2), z(z2) {}
  union {
    struct { double x, y, z; };
    struct { double r, g, b; };
  };
  Vec3 normalize();
};

Vec3 operator+(const Vec3 &a, const Vec3 &b);
Vec3 operator-(const Vec3 &a, const Vec3 &b);
Vec3 operator*(double a, const Vec3 &b);
Vec3 operator/(const Vec3 &a, double b);
bool operator==(const Vec3 &a, const Vec3 &b);
bool operator!=(const Vec3 &a, const Vec3 &b);
Vec3 cross(const Vec3 &a, const Vec3 &b);
double dot(const Vec3 &a, const Vec3 &b);

typedef Vec3 Color;
typedef Vec3 Point;
typedef Vec3 Vector;

class Ray {
public:
  const Point origin;
  const Vector dir;
    
  Ray(const Point &o, const Vector &d) : origin(o), dir(d) {}
};

#endif
