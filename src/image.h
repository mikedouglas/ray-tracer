#ifndef IMAGE_H
#define IMAGE_H

#include "vec3.h"

class Image {
private:
  Color *image;
  int width, height;
  void create_image(int width, int height);

public:
  Image(int width, int height) : width(width), height(height) {
    create_image(width, height);
  }
  void write_png(ofstream *out);
};

#endif
