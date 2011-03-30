#ifndef SCENE_H
#define SCENE_H

#include "shape.h"
#include "light.h"
#include "vec3.h"
#include "constants.h"

class Scene {
    unsigned int n_shapes, n_lights;
    Shape *shapes[MAX_SHAPES];
    Light *lights[MAX_LIGHTS];
    Point eye;
    
public:
    Scene(Point eye) : eye(eye), n_shapes(0), n_lights(0) {}
    Color trace(const Ray &ray);
    void render();
    void addShape(Shape *s);
    void addLight(Light *l);
};

#endif