//DImage.cpp
#include "DImage.h"
#include "png.h"
// See http://zarb.org/~gc/html/libpng.html
//     https://gist.github.com/niw/5963798
bool DImage::load(std::string filePath)
{
  // Open file to read.
  png_FILE_p file = nullptr;
  fopen_s(&file, filePath.c_str(), "rb");
  if (!file) {
    return false;
  }
  // 8 is the maximum size that can be checked
  constexpr png_byte signatureSize = 8;
  png_byte header[signatureSize];
  // Read the signature.
  const int byteRead = fread_s(header, sizeof(header), 1, signatureSize, file);
  // The file should have at least 8 bytes size.
  if(byteRead != signatureSize) {
    fclose(file);
    return false;
  }

  const bool IsPngValid = !png_sig_cmp(header, 0, signatureSize);
  if (!IsPngValid) {
    fclose(file);
    return false;
  }
  // Create png structure.
  png_structp  png = png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png) {
    fclose(file);
    return false;
  }
  // Create info structure.
  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(file);
    png_destroy_read_struct(&png, nullptr, nullptr);
    return false;
  }
  // Set error handler if an error occurs.
  if (setjmp(png_jmpbuf(png)))
  {
    fclose(file);
    png_destroy_read_struct(&png, &info, nullptr);
    return false;
  }
  // Enable I/O methods.
  png_init_io(png, file);
  // Tell libpng that 8 bytes are missing from the start after we read signature above.
  png_set_sig_bytes(png, signatureSize);  
  // Bit depth always 8. No palette. Always BGRA.
  int transforms = PNG_TRANSFORM_GRAY_TO_RGB | PNG_TRANSFORM_BGR;
  // Read entire image.
  png_read_png(png, info, transforms, 0);
  // Reading done. Release the file.
  fclose(file);

  uint32 width = png_get_image_width(png, info);
  uint32 height = png_get_image_height(png, info);
  int channelNumber = png_get_channels(png, info); // Always 3 or 4 channels
  png_bytepp rows = png_get_rows(png, info);

  auto Channels4 = [](DColor& color, png_bytep pixel) {
    color = *reinterpret_cast<uint32*>(pixel);
  };
  auto Channels3 = [](DColor& color, png_bytep pixel) {
    color.set(pixel[2], pixel[1], pixel[0]);
  };
  using fillChannelFunc = void(DColor&, png_bytep);
  auto fillPixels = [height, width, rows, &pixels = this->m_pixels, channelNumber]
    (fillChannelFunc fillFunc) {
    for (uint32 i = 0; i < height; ++i)
    {
      png_bytep pixel = rows[i];
      for (uint32 j = 0; j < width; ++j)
      {
        fillFunc(pixels[i][j], pixel);
        pixel += channelNumber;
      }
    }
  };

  m_pixels.size(width, height);
  if (channelNumber == 4)
  {
    fillPixels(Channels4);
  }
  else
  {
    fillPixels(Channels3);
  }
  // Release structures.
  png_destroy_read_struct(&png, &info, NULL);
  return true;
}

bool DImage::save(std::string filePath)
{
  // Open file to write.
  png_FILE_p file = nullptr;
  fopen_s(&file, filePath.c_str(), "wb");
  if (!file) {
    return false;
  }
  // Create png structure.
  png_structp  png = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
  if (!png) {
    fclose(file);
    return false;
  }
  // Create info structure.
  png_infop info = png_create_info_struct(png);
  if (!info) {
    fclose(file);
    png_destroy_write_struct(&png, nullptr);
    return false;
  }
  // Set error handler if an error occurs.
  if (setjmp(png_jmpbuf(png)))
  {
    fclose(file);
    png_destroy_write_struct(&png, &info);
    return false;
  }

  // Enable I/O methods.
  png_init_io(png, file);
  // Set header info.
  png_set_IHDR(png, info, m_pixels.width(), m_pixels.height(), 8, PNG_COLOR_TYPE_RGB_ALPHA,
    PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
  // Set image data.
  auto raws = reinterpret_cast<png_bytepp>(const_cast<DColor**>(m_pixels.grid()));
  png_set_rows(png, info, raws);
  // Write entire image. Use BGR to RGB transformation.
  png_write_png(png, info, PNG_TRANSFORM_BGR, NULL);
  // Writing done. Release the file.
  fclose(file);
  // Release structures.
  png_destroy_write_struct(&png, &info);
  return false;
}

DColor* DImage::data()
{
  return m_pixels.raw();
}

const DColor* DImage::data() const
{
  return m_pixels.raw();
}

DColor* const* DImage::pixels()
{
  return m_pixels.grid();
}

const DColor* const* DImage::pixels() const
{
  return m_pixels.grid();
}

DSize DImage::size() const
{
  return m_pixels.size();
}
