#include "scene.h"
#include "sphere.h"
#include "vec3.h"
#include "constants.h"
#include "image.h"

#include <cmath>
#include <cassert>

void Scene::addLight(Light *l) {
    if (n_lights < MAX_LIGHTS)
        lights[n_lights++] = l;
}

void Scene::addShape(Shape *s) {
    if (n_shapes < MAX_SHAPES)
        shapes[n_shapes++] = s;
}

double Scene::testShadow(Shape *s, Light *l, Ray lightray) {
  double dist_light = l->distance(lightray.origin);

  for (int i = 0; i < n_shapes; i++) {
    if (shapes[i] != s) {
      double dist = shapes[i]->intersect(lightray);
      if (dist > 0 && dist < dist_light)
        return 0;
    }
  }

  return l->brightness;
}

Color Scene::shade(Shape *s, const Ray &ray, const Ray &nrm) {
  Color c = s->getSurface()->color;
  double k = -2 * dot(ray.dir, nrm.dir);
  Ray refl(nrm.origin, k*nrm.dir + ray.dir);

  for (int i = 0; i < n_lights; i++) {
    Light *light = lights[i];
    Ray to_light = light->to_light(nrm.origin);
    double diffuse = dot(nrm.dir, to_light.dir);

    if (diffuse > 0.0) {
      double brightness = testShadow(s, light, to_light);
      diffuse *= brightness;
      c = c + light->color*diffuse;

      double spec = dot(refl.dir, to_light.dir);
      if (spec > 0.0) {
        spec = brightness * pow(spec, s->getSurface()->s_coef);
        c = c + light->color*spec;
      }
    }
  }

  return c;
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
  
  Point at = ray.origin + min_t*ray.dir;
  return shade(closest, ray, Ray(at, closest->normal(at)));
}

Image *Scene::render() {
  Image *img = new Image(WIDTH, HEIGHT);

  for (int i = 0; i < HEIGHT; i++) {
    for (int j = 0; j < WIDTH; j++) {
      Point pixel(j, HEIGHT-1-i, 0);
      Ray ray(eye, (pixel-eye).normalize());
      img->setColor(j, i, trace(ray));
    }
  }

  return img;
}
