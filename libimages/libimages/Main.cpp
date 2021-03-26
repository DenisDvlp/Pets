#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <xstring>

#define PNG_DEBUG 3
#include "png.h"

class Image
{
public:
  bool load(std::string);
  bool save(std::string);
  png_byte **data;
  int width = 0;
  int height = 0;
  png_byte color_type;
  png_byte bit_depth;
  png_structp png_ptr;
  int **pixels;
};

void abort_(const char * s, ...)
{
  va_list args;
  va_start(args, s);
  vfprintf(stderr, s, args);
  fprintf(stderr, "\n");
  va_end(args);
  abort();
}

int x, y;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void read_png_file(const char* file_name)
{
  unsigned char header[8];    // 8 is the maximum size that can be checked

                     /* open file and test for it being a png */
  FILE *fp = nullptr;
  fopen_s(&fp, file_name, "rb");
  if (!fp)
    abort_("[read_png_file] File %s could not be opened for reading", file_name);
  fread_s(header, 8, 1, 8, fp);
  if (png_sig_cmp(header, 0, 8))
    abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);


  /* initialize stuff */
  png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    abort_("[read_png_file] png_create_read_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    abort_("[read_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[read_png_file] Error during init_io");

  png_init_io(png_ptr, fp);
  png_set_sig_bytes(png_ptr, 8);

  png_read_info(png_ptr, info_ptr);

  width = png_get_image_width(png_ptr, info_ptr);
  height = png_get_image_height(png_ptr, info_ptr);
  color_type = png_get_color_type(png_ptr, info_ptr);
  bit_depth = png_get_bit_depth(png_ptr, info_ptr);

  number_of_passes = png_set_interlace_handling(png_ptr);
  png_read_update_info(png_ptr, info_ptr);


  /* read file */
  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[read_png_file] Error during read_image");

  row_pointers = (png_bytep*)malloc(sizeof(png_bytep) * height);
  for (y = 0; y<height; y++)
    row_pointers[y] = (png_byte*)malloc(png_get_rowbytes(png_ptr, info_ptr));

  png_read_image(png_ptr, row_pointers);

  fclose(fp);
}


void write_png_file(const char* file_name)
{
  /* create file */
  FILE *fp = nullptr;
  fopen_s(&fp, file_name, "wb");
  if (!fp)
    abort_("[write_png_file] File %s could not be opened for writing", file_name);


  /* initialize stuff */
  png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr)
    abort_("[write_png_file] png_create_write_struct failed");

  info_ptr = png_create_info_struct(png_ptr);
  if (!info_ptr)
    abort_("[write_png_file] png_create_info_struct failed");

  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[write_png_file] Error during init_io");

  png_init_io(png_ptr, fp);


  /* write header */
  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[write_png_file] Error during writing header");

  png_set_IHDR(png_ptr, info_ptr, width, height,
    bit_depth, color_type, PNG_INTERLACE_NONE,
    PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

  png_write_info(png_ptr, info_ptr);


  /* write bytes */
  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[write_png_file] Error during writing bytes");

  png_write_image(png_ptr, row_pointers);


  /* end write */
  if (setjmp(png_jmpbuf(png_ptr)))
    abort_("[write_png_file] Error during end of write");

  png_write_end(png_ptr, NULL);

  /* cleanup heap allocation */
  for (y = 0; y<height; y++)
    free(row_pointers[y]);
  free(row_pointers);

  fclose(fp);
}


void process_file(void)
{
  if (png_get_color_type(png_ptr, info_ptr) == PNG_COLOR_TYPE_RGB)
    abort_("[process_file] input file is PNG_COLOR_TYPE_RGB but must be PNG_COLOR_TYPE_RGBA "
      "(lacks the alpha channel)");

  if (png_get_color_type(png_ptr, info_ptr) != PNG_COLOR_TYPE_RGBA)
    abort_("[process_file] color_type of input file must be PNG_COLOR_TYPE_RGBA (%d) (is %d)",
      PNG_COLOR_TYPE_RGBA, png_get_color_type(png_ptr, info_ptr));

  for (y = 0; y<height; y++) {
    png_byte* row = row_pointers[y];
    for (x = 0; x<width; x++) {
      png_byte* ptr = &(row[x * 4]);
      printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
        x, y, ptr[0], ptr[1], ptr[2], ptr[3]);

      /* set red value to 0 and green value to the blue one */
      ptr[0] = 0;
      ptr[1] = ptr[2];
    }
  }
}


int main(int argc, char **argv)
{
  Image image;
  image.load("ex.png");
  image.save("exz2.png");
  return 0;
}

bool Image::load(std::string filePath)
{
  FILE* file = nullptr;
  fopen_s(&file, filePath.c_str(), "rb");

  if (!file) return false;

  unsigned char header[8]; // 8 is the maximum size that can be checked

  fread_s(header, sizeof(header), 1, 8, file);

  if (png_sig_cmp(header, 0, 8)) return false; // if PNG signature is found

  auto png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) return false;

  auto info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr) return false;

  int channelNumber = 0;
  png_colorp palette = nullptr;
  int num_palette = 0;
  png_bytep alpha_palette = nullptr;
  int num_alpha_palette = 0;

  try
  {
    png_init_io(png_ptr, file);
    png_set_sig_bytes(png_ptr, 8);
    png_read_info(png_ptr, info_ptr);

    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);

    if (color_type & PNG_COLOR_MASK_PALETTE)
    {
      png_get_PLTE(png_ptr, info_ptr, &palette, &num_palette);
      if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      {
        png_get_tRNS(png_ptr, info_ptr, &alpha_palette, &num_alpha_palette, nullptr);
      }
    }

    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    channelNumber = png_get_channels(png_ptr, info_ptr);
    data = new png_byte*[height];
    for (int y = 0; y < height; ++y)
      data[y] = new png_byte[rowbytes];

    png_read_image(png_ptr, data); // read raw data

    fclose(file);
  }
  catch (...)
  {
    fclose(file);
    return false;
  }

  pixels = new int*[height];
  for (int y = 0; y < height; ++y)
    pixels[y] = new int[width];

  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      auto ptr = data[y] + (channelNumber * x);

      int alpha = 0xFF;

      if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
      {
        alpha = alpha_palette[*ptr];
      }
      else if (color_type & PNG_COLOR_MASK_ALPHA)
      {
        alpha = ptr[3];
      }

      pixels[y][x] = alpha << 24;

      if (color_type & PNG_COLOR_MASK_PALETTE)
      {
        auto& channels = palette[*ptr];
        pixels[y][x] |= channels.red << 16 | channels.green << 8 | channels.blue;
      }
      else if (color_type & PNG_COLOR_MASK_COLOR)
      {
        pixels[y][x] |= ptr[0] << 16 | ptr[1] << 8 | ptr[2];
      }
      else
      {
        pixels[y][x] |= ptr[0] << 16 | ptr[0] << 8 | ptr[0];
      }
    }
  }

  return true;
}

bool Image::save(std::string filePath)
{
  FILE *file = nullptr;
  fopen_s(&file, filePath.c_str(), "wb");

  if (!file) return false;

  auto png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png_ptr) return false;

  auto info_ptr = png_create_info_struct(png_ptr);

  if (!info_ptr) return false;

  try
  {
    png_init_io(png_ptr, file);
    png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth, PNG_COLOR_TYPE_RGB_ALPHA, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
    png_write_info(png_ptr, info_ptr);

    png_bytepp tmp = new png_bytep[height];
    for (int y = 0; y < height; ++y)
      tmp[y] = new png_byte[width * 4];

    for (int y = 0; y < height; ++y)
      for (int x = 0; x < width; ++x)
      {
        int index = x * 4;
        int pixel = pixels[y][x];
        tmp[y][index    ] = (pixel & 0x00FF0000) >> 16;
        tmp[y][index + 1] = (pixel & 0x0000FF00) >> 8;
        tmp[y][index + 2] = pixel & 0x000000FF;
        tmp[y][index + 3] = (pixel & 0xFF000000) >> 24;
      }

    png_write_image(png_ptr, tmp);
    png_write_end(png_ptr, nullptr);
  }
  catch (...)
  {
    return false;
  }

  fclose(file);

  return true;
}
