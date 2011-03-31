#include "image.h"
#include <cassert>
#include <fstream>
#include <png.h>

void Image::create_image(int width, int height) {
  assert(width*height > 0);
  image = new Color[width*height];
}

void Image::write_png(ofstream *out) {
  
}
