#include "scene.h"
#include "sphere.h"
#include "vec3.h"
#include "constants.h"
#include "image.h"

#include <cstdio> // REMOVE
#include <cstdlib>

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
    if (t > 0 && (!closest || t < min_t)) {
      closest = shapes[i];
      min_t = t;
    }
  }

  if (!closest)
    return Color(0,0,0); // TODO: allow custom background colors
  
  return closest->getSurface()->color;
}

Image *Scene::render() {
  Image *img = new Image(WIDTH, HEIGHT);

  for (int i = 0; i < WIDTH; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      Ray ray(eye, (Vector(j, i, 0)-eye).normalize());
      img->setColor(j, i, trace(ray));
    }
  }

  return img;
}
