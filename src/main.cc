#include "scene.h"
#include "surface.h"
#include "sphere.h"
#include "light.h"
#include "image.h"

#include <iostream>

int main (int argc, const char * argv[])
{
  Scene scene(Point(200, 200, 1000));
  Surface surr(Color(150,0,0), 8, 0.1, 0);
  Surface surb(Color(0, 0, 200), 5, 0.2, 0);
  Surface surb2(Color(0, 0, 200), 5, 0, 0.3);
  Surface surg(Color(0,200,0), 8, 0, 0);
  scene.addShape(new Sphere(&surr, 70, 90, 320, 100));
  scene.addShape(new Sphere(&surb2, 40, 320, 85, 85));
  scene.addShape(new Sphere(&surr, 80, 440, 120, 0));
  scene.addShape(new Sphere(&surg, 60, 360, 400, 50));
  Light l(Point(200,200,200), Color(255,219,88), 0.5);
  scene.addLight(&l);
  Image *img = scene.render();
  img->write_png(argv[1]); 
  return 0;
}

