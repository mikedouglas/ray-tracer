#ifndef SCENE_H
#define SCENE_H

#include <iostream>
#include <fstream>
#include "shape.h"
#include "light.h"
#include "vec3.h"
#include "image.h"
#include "constants.h"

class Scene {
  int n_shapes, n_lights;
  Shape *shapes[MAX_SHAPES];
  Light *lights[MAX_LIGHTS];
  Point eye;
    
public:
  Scene(Point eye) : eye(eye), n_shapes(0), n_lights(0) {}
  Color shade(Shape *s, const Ray &ray, const Ray &nrm);
  Color trace(const Ray &ray);
  Image *render();
  void addShape(Shape *s);
  void addLight(Light *l);
private:
  double testShadow(Shape *s, Light *l, Ray lightray);
};

#endif
