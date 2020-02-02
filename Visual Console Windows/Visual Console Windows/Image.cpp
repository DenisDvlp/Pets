//Image.cpp
#include "Image.h"
#include "png.h"

bool Image::load(std::string filePath)
{
  FILE* file = nullptr;
  fopen_s(&file, filePath.c_str(), "rb");

  if (!file) return false;

  unsigned char header[8]; // 8 is the maximum size that can be checked

  fread_s(header, sizeof(header), 1, 8, file);

  if (png_sig_cmp(header, 0, 8)) return false; // if PNG signature is found

  auto png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  if (!png) return false;

  auto info = png_create_info_struct(png);

  if (!info) return false;

  int width = 0;
  int height = 0;
  png_byte colorType = 0;
  int channelNumber = 0;
  png_byte bit_depth = 8; // assume that it is always 8

  png_colorp palette = nullptr;
  png_bytep alphaPalette = nullptr;
  png_bytepp rawData = nullptr;

  bool hasAlpha = false;
  bool hasColor = false;
  bool hasPalette = false;
  bool hasAlphaPallete = false;

  try
  {
    png_init_io(png, file);
    png_set_sig_bytes(png, 8);
    png_read_info(png, info);

    width = png_get_image_width(png, info);
    height = png_get_image_height(png, info);
    colorType = png_get_color_type(png, info);
    channelNumber = png_get_channels(png, info);
    //bit_depth = png_get_bit_depth(png, info);

    hasAlpha = colorType & PNG_COLOR_MASK_ALPHA;
    hasColor = colorType & PNG_COLOR_MASK_COLOR;
    hasPalette = colorType & PNG_COLOR_MASK_PALETTE;
    hasAlphaPallete = png_get_valid(png, info, PNG_INFO_tRNS);

    if (hasPalette)
    {
      png_get_PLTE(png, info, &palette, nullptr);
      if (hasAlphaPallete)
      {
        png_get_tRNS(png, info, &alphaPalette, nullptr, nullptr);
      }
    }

    int rowBytes = png_get_rowbytes(png, info);
    rawData = new png_byte*[height];
    for (int y = 0; y < height; ++y)
      rawData[y] = new png_byte[rowBytes];

    png_read_image(png, rawData); // read raw data

    fclose(file);
  }
  catch (...)
  {
    fclose(file);
    return false;
  }

  m_pixels.size(height, width);

  for (int y = 0; y < height; y++) {
    auto ptr = rawData[y];
    for (int x = 0; x < width; x++, ptr += channelNumber) {

      /*int alpha = 0xFF;

      if (hasAlphaPallete)
      {
        alpha = alphaPalette[*ptr];
      }
      else if (hasAlpha)
      {
        alpha = ptr[3];
      }

      pixels[y][x] = alpha << 24;*/

      if (hasPalette)
      {
        auto& channels = palette[*ptr];
        m_pixels[y][x].set(channels.red, channels.green, channels.blue);
      }
      else if (hasColor)
      {
        m_pixels[y][x].set(ptr[0], ptr[1], ptr[2]);
      }
      else
      {
        m_pixels[y][x].set(ptr[0], ptr[0], ptr[0]);
      }
    }
  }

  return true;
}

bool Image::save(std::string)
{
  return false;
}

Color* const* Image::pixels()
{
  return m_pixels.grid();
}

const Color* const* Image::pixels() const
{
  return m_pixels.grid();
}

Size Image::size() const
{
  return m_pixels.size();
}
