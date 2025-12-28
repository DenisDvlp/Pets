// png2hex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "DImage.hpp"
#include "DString.hpp"
#include "ExtIntArray.hpp"
#include <iostream>
#include <bitset>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

static constexpr uint8_t BITS_IN_BYTE = 8;

class FontInfo {
public:
  static constexpr int8_t OFFSET_BITS = 10;
  FontInfo() : offsets(offsetsData) {}
  ExtIntArray<int, OFFSET_BITS> offsets;
  int offsetsSize = 0;
  DBiArray<unsigned char> output;
  unsigned char offsetsData[2000] = {};
};

DBiArray<unsigned char> convertToBitsHelper(const DImage& img, uint8 threshold, int isFont) {
  const auto fromLine = isFont ? 1 : 0;
  const auto colorDepth = isFont ? 1 : 2;
  const DSize imgSize = img.size();
  const int16 widthOut = (imgSize.width() * colorDepth / BITS_IN_BYTE + ((imgSize.width() * colorDepth) % BITS_IN_BYTE ? 1 : 0));

  DBiArray<unsigned char> output;
  output.size(widthOut, imgSize.height() - fromLine);

  bitset<BITS_IN_BYTE> bits;
  for (size_t i = fromLine, k = 0; i < imgSize.height(); i++)
  {
    for (size_t j = 0; j < imgSize.width(); ++k)
    {
      bits.reset();
      for (int l = BITS_IN_BYTE - 1; l >= 0 && j < imgSize.width(); ++j, l -= colorDepth)
      {
        // Turn colored pixel into grayscale. Use Luma coding Rec. 601:
        //   Y = 0.299 * R + 0.587 * G + 0.114 * B;
        // BRIGHT pixels are 0's (background), DARK pixels are 1's.
        // Brightness is in range of [0, 255].
        // Bright pixels are >=128. Dark pixels are <128.
        const DColor color = img[i][j];
        const double brightness = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
        const auto isDark = (brightness < threshold);
        bits.set(l, isDark);
        if (isFont)
          continue;
        const auto isTransparent = (color.alpha() < 127);
        bits.set(l - 1, isTransparent);
      }
      output.raw()[k] = static_cast<unsigned char>(bits.to_ulong());
    }
  }
  return output;
}

FontInfo readFontInfo(const DImage& img, uint8 threshold) {
  FontInfo fi;
  const DSize imgSize = img.size();

  short k = 0;
  for (int i = 0; i < imgSize.width(); ++i)
  {
    if(img[0][i] == DColors::BLACK)
      fi.offsets[k++] = i;
  }
  fi.offsets[k++] = imgSize.width();
  fi.offsetsSize = k * FontInfo::OFFSET_BITS / BITS_IN_BYTE + bool(k * FontInfo::OFFSET_BITS % BITS_IN_BYTE);

  fi.output = convertToBitsHelper(img, threshold, true);

  return fi;
}

DBiArray<unsigned char> convertToBits(const DImage& img, uint8 threshold) {
  return convertToBitsHelper(img, threshold, false);
}

std::string getStringArray(const unsigned char* output, size_t size, std::string name) {
  static constexpr size_t HEX_IN_ROW = 12;
  static const char lookupHexTable[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  if (size == 0) {
    return "";
  }

  std::stringstream ss;
  ss << "static const uint8_t " << name << "[" << size << "] PROGMEM = {";
  for (size_t i = 0; i < size; ++i)
  {
    if (i % HEX_IN_ROW == 0) {
      ss << "\n  ";
    }
    ss << "0x" << lookupHexTable[output[i] >> 4] << lookupHexTable[output[i] & 0xF] << ", ";
  }
  ss << "\n};\n";

  return ss.str();
}

std::string getBitmapString(const unsigned char* output, int realWidth, int width, int height, std::string name, bool isFont) {
  size_t outSize = width * height;
  if (outSize == 0) {
    return "";
  }

  std::string pngName = "png_" + name;
  std::stringstream ss;
  ss << getStringArray(output, outSize, pngName);

  // get full structs
  std::string bmpName("bmp_");
  bmpName.append(name);
  std::string picName("pic_");
  picName.append(name);
  ss << "const Bitmap " << bmpName << "(" << pngName << ", " << (width * (isFont ? 8 : 4)) << ", " << height << ", " << (isFont ? 1 : 2) << ");\n"
    "const Picture " << picName << "(" << bmpName << ", 0, 0, " << realWidth << ", " << height << ");\n\n";

  return ss.str();
}

bool appendToFile(const std::string& filepath, const std::string& text, bool rewrite = false) {
  if (text.empty()) {
    return true;
  }
  fstream headerFile(filepath, std::ios_base::out | (rewrite ? 0 :std::ios_base::app));
  if (!headerFile.is_open()) {
    return false;
  }
  headerFile << text;
  headerFile.close();
  return true;
}

DVector<std::string> readFromFile(std::string filepath)
{
  fstream imgfile(filepath, std::ios_base::in);
  if (!imgfile.is_open()) {
    return {};
  }
  DVector<std::string> list;
  std::string str;
  while (!imgfile.eof()) {
    std::getline(imgfile, str);
    if (!str.empty()) {
      list.push(str);
    }
  }
  imgfile.close();
  return list;
}

std::filesystem::path getAbsolutePath(const char* strPath, std::filesystem::path parent = std::filesystem::current_path()) {
  auto absPath = std::filesystem::path(strPath).lexically_normal();
  if (absPath.is_relative()) {
    if (absPath.wstring().front() == std::filesystem::path::preferred_separator)
      absPath = (parent += absPath);
    else
      absPath = parent / absPath;
  }
  return absPath.lexically_normal();
}

bool isFile(const std::filesystem::path& p) {
  return !std::filesystem::is_directory(p);
}

int main(int argNum, const char** args)
{
  if (argNum != 4) {
    const char helpText[] = R"(
This program read `imglist.txt` which contains a list of image names. It converts
the images into PROGMEM arrays of HEX values suitable for Arduino projects.

Usage: png2hex <path to text file with image list> <output header path> <output source path>

imglist.txt:
  filepath/img1.png -t200
  img1.png
  img2.png -t128
  fontpic.png -f"

imglist.txt flags:
-t<n>  flag with a following value of the threshold after the image path.
       All pixels with brightness higher than the given threshold are considered
       as a background(or white), otherwise those, which are lower than the threshold,
       are considered as black pixels. The threshold `-t` flag is not mandatory.
       Default value is 128. The threshold shall be in range of [0, 255].
       Note: image file path shall be without spaces.
-f     flag indicates this is a font image.
       The first line of pixels in font image shall be for metrics which denotes
       the offset of each particular letter. The remaining lines is for the
       graphical representation of letters.
)";
    std::cout << helpText;
    return 0;
  }

  auto inputImageListPath = getAbsolutePath(args[1]);
  if (!isFile(inputImageListPath)) {
    std::cout << "Image list file does not exist or corrupted";
    return 1;
  }

  auto outputHeaderPath = getAbsolutePath(args[2]);
  if (std::filesystem::is_directory(outputHeaderPath)) {
    std::cout << "Output header file is an existing directory";
    return 1;
  }

  auto outputSourcePath = getAbsolutePath(args[3]);
  if (std::filesystem::is_directory(outputSourcePath)) {
    std::cout << "Output source file is an existing directory";
    return 1;
  }

  std::string includes = "#pragma once\n#include \"Picture.hpp\"\n\n";

  auto headerStr = outputHeaderPath.string();
  appendToFile(headerStr, includes, true);

  includes =
    "#include \"" + outputHeaderPath.filename().string() + "\"";
  includes += R"(
#ifdef ARDUINO
#include <avr/pgmspace.h>
#else
# define PROGMEM
#endif

)";

  auto cppStr = outputSourcePath.string();
  appendToFile(cppStr, includes, true);

  size_t totalNumberOfBytes = 0;

  auto imgList = readFromFile(inputImageListPath.string());
  for (DString command : imgList)
  {
    // font flag
    const bool isFont = command.find(" -f") != command.end();
    // threashold flag
    uint8 threshold = 128;
    auto it = command.find(" -t");
    if (it != command.end()) {
      const char *str = &*(it + 3);
      threshold = static_cast<uint8>(std::atoi(str));
    }
    // extract name
    it = command.find(".png");
    if (it != command.end()) {
      command.assign(command.cbegin(), it + 4);
    }

    DImage img;
    auto imgPath = getAbsolutePath(command.data(), inputImageListPath.parent_path());
    if (!img.load(imgPath.string())) {
      std::cout << "Unable to read image `" << imgPath << "`. Skipped." << endl;
      continue;
    }
    std::cout << (isFont ? "Font" : "Image") << " `" << imgPath << "` read." << endl;

    command.remove(".png");

    if (isFont) {
      FontInfo fi = readFontInfo(img, threshold);
      totalNumberOfBytes += fi.output.size().square() + fi.offsetsSize;
      std::string bitmapArray = getBitmapString(fi.output.raw(), img.size().width(), fi.output.size().width(), fi.output.size().height(), command.data(), isFont);
      DString offsetName = "font_offsets_" + command;
      std::string offsetsArray = getStringArray(fi.offsetsData, fi.offsetsSize, offsetName.data());
      stringstream ss;
      ss << "// Each offset value contains " << int(FontInfo::OFFSET_BITS) << " bits. Use `ExtIntArray` to read.\n" << offsetsArray;
      offsetsArray = std::move(ss.str());
      if (!appendToFile(cppStr, offsetsArray)) {
        std::cout << "Unable to write to file `" << cppStr << "`." << endl;
        return 1;
      }
      if (!appendToFile(cppStr, bitmapArray)) {
        std::cout << "Unable to write to file `" << cppStr << "`." << endl;
        return 1;
      }
      DString structs =
        "extern const Bitmap bmp_" + command +
        ";\nextern const Picture pic_" + command +
        ";\nextern const uint8_t font_offsets_" + command + "[];\n\n";
      if (!appendToFile(headerStr, structs.data())) {
        std::cout << "Unable to write to file `" << headerStr << "`." << endl;
        return 1;
      }
    }
    else {
      DBiArray<unsigned char> output = convertToBits(img, threshold);
      totalNumberOfBytes += output.size().square();
      std::string array = getBitmapString(output.raw(), img.size().width(), output.size().width(), output.size().height(), command.data(), isFont);
      if (!appendToFile(cppStr, array)) {
        std::cout << "Unable to write to file `" << cppStr << "`." << endl;
        return 1;
      }
      DString structs =
        "extern const Bitmap bmp_" + command +
        ";\nextern const Picture pic_" + command + ";\n\n";
      if (!appendToFile(headerStr, structs.data())) {
        std::cout << "Unable to write to file `" << headerStr << "`." << endl;
        return 1;
      }
    }
  }
  std::cout << "Generated `" << headerStr << "`." << endl;
  std::cout << "Generated `" << cppStr << "`." << endl;
  std::cout << "Total PROGMEM bytes used:" << totalNumberOfBytes << endl;
  std::cout << "Done." << endl;
  return 0;
}
