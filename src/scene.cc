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
        return shapes[i]->getSurface()->transp * l->brightness; // if it's in the shadows
    }
  }

  return l->brightness;
}

int inception = 0;
#define MAX_INCEPTION 5

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

  // calculate reflection off other objects, but don't go too deep
  double reflk = s->getSurface()->refl;
  if (reflk > 0 && inception < MAX_INCEPTION) {
    inception++;
    Color refl_c = trace_avoid(refl, s);
    c = c + refl_c * reflk;
    inception--;
  }

  // calculate colors for transparent objects
  double transk = s->getSurface()->transp;
  if (transk > 0) {
    c = (1-transk) * c;
    Color trans_c = trace_avoid(ray, s);
    c = c + trans_c * transk; 
  }

  return c;
}

Color Scene::trace(const Ray &ray) {
  return trace_avoid(ray, NULL);
}

#define FAR_AWAY -500.0
Color checkerboard(const Ray &ray) {
  if (ray.dir.z > -0.9) return Color(0,0,0);

  Point intersect = ray.origin + ray.dir*(FAR_AWAY/ray.dir.z);
  if ((((int)intersect.x/15) + ((int)intersect.y/15)) % 2)
    return Color(50,50,50);
  else
    return Color(255,255,255);
}

// terrible hack, need to sometimes avoid a shape,
// and C++'s default arguments aren't cooperating
Color Scene::trace_avoid(const Ray &ray, Shape *s) {
  double t, min_t = 0;
  Shape *closest = NULL;
    
  for (int i = 0; i < n_shapes; i++) {
    t = shapes[i]->intersect(ray);
    if (t > 0 && (!s || s != shapes[i]) && (!closest || t < min_t)) {
      closest = shapes[i];
      min_t = t;
    }
  }

  if (!closest)
    return checkerboard(ray);
  
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
