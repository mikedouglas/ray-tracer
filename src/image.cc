#include "constants.h"
#include "image.h"
#include <cmath>
#include <cassert>
#include <fstream>
#include <png.h>

#define COLOR_TO_16BIT(x) ((x.b%32) + ((x.g%32) << 6) + ((r%32) << 11))

// TODO: remove
void setRGB(png_byte *ptr, Color val)
{
  ptr[0] = (float)val.r;
  ptr[1] = (float)val.g;
  ptr[2] = (float)val.b;
}

double scale(double val) {
  val /= 255.0;
  
  if (val > 1.0)
    val = 1.0;
  else if (val < 0.0)
    val = 0.0;

  val = exp(log(val)/GAMMA);
  val *= 255.0;

  return val;
}

Color gamma_correct(const Color &c) {
  return Color(scale(c.r), scale(c.g), scale(c.b));
}

void Image::create_image(int width, int height) {
  assert(width*height > 0);
  image = new Color[width*height];

  png_ptr = png_create_write_struct
    (PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
  info_ptr = png_create_info_struct(png_ptr);
}

void Image::write_png(char *fname) {
  FILE *fp = fopen(fname, "wb");

  png_init_io(png_ptr, fp);
  png_set_IHDR(png_ptr, info_ptr, width, height, 8, PNG_COLOR_TYPE_RGB,
               PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE,
               PNG_FILTER_TYPE_BASE);
  png_write_info(png_ptr, info_ptr);

  png_bytep row = (png_bytep) malloc(3 * width * sizeof(png_byte));
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      setRGB(&(row[j*3]), image[i*width + j]);
    }
    png_write_row(png_ptr, row);
  }

  png_write_end(png_ptr, NULL);
  fclose(fp);
  free(row);
}
