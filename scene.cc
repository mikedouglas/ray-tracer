#include "scene.h"
#include "vec3.h"
#include "constants.h"

void Scene::addLight(Light *l) {
    if (n_lights < MAX_LIGHTS)
        lights[n_lights++] = l;
}

void Scene::addShape(Shape *s) {
    if (n_shapes < MAX_SHAPES)
        shapes[n_shapes++] = s;
}

Color Scene::trace(const Ray &ray) {
    double t, min_t = 0;
    Shape *closest = NULL;
    
    for (int i = 0; i < n_shapes; i++) {
        t = shapes[i]->intersect(ray);
        if (t > 0 && (!closest || t < min_t))
            closest = shapes[i];
    }
    
    if (!closest)
        return Color(0,0,0); // TODO: allow custom background colors
    
    return closest->surface->color;
}

void Scene::render() {
    
}