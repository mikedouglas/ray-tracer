#ifndef IMAGE_H
#define IMAGE_H

#include <fstream>
#include <png.h>
#include "vec3.h"

class Image {
private:
  Color *image;
  int width, height;
  png_structp png_ptr;
  png_infop info_ptr;
  void create_image(int width, int height);

public:
  Image(int width, int height) : width(width), height(height) {
    create_image(width, height);
  }
  void write_png(char *fname);
};

#endif
