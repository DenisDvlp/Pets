// png2hex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "DImage.h"
#include "DString.h"
#include "ExtIntArray.h"
#include <iostream>
#include <bitset>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

static constexpr int8_t BITS_IN_BYTE = 8;


class FontInfo {
public:
  static constexpr int8_t OFFSET_BITS = 10;
  FontInfo() : offsets(offsetsData) {}
  ExtIntArray<int, OFFSET_BITS> offsets;
  int offsetsSize = 0;
  DBiArray<unsigned char> output;
  unsigned char offsetsData[2000] = {};
};

DBiArray<unsigned char> convertToBitsHelper(const DImage& img, uint8 threshold, int fromLine = 0) {
  const DSize imgSize = img.size();
  const int16 widthOut = (imgSize.width() / BITS_IN_BYTE +
    (imgSize.width() % BITS_IN_BYTE ? 1 : 0));

  DBiArray<unsigned char> output;
  output.size(widthOut, imgSize.height() - fromLine);

  bitset<BITS_IN_BYTE> bits;
  for (size_t i = fromLine, k = 0; i < imgSize.height(); i++)
  {
    for (size_t j = 0; j < imgSize.width(); ++k)
    {
      bits.reset();
      for (int k = BITS_IN_BYTE - 1; k >= 0 && j < imgSize.width(); ++j, --k)
      {
        // Turn colored pixel into grayscale. Use Luma coding Rec. 601:
        //   Y = 0.299 * R + 0.587 * G + 0.114 * B;
        // BRIGHT pixels are 0's (background), DARK pixels are 1's.
        // Brightness is in range of [0, 255].
        // Bright pixels are >=128. Dark pixels are <128.
        const DColor color = img[i][j];
        const double brightness = 0.299 * color.red() + 0.587 * color.green() + 0.114 * color.blue();
        bits.set(k, /*isDark*/ brightness < threshold);
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

  fi.output = convertToBitsHelper(img, threshold, 1);

  return fi;
}

DBiArray<unsigned char> convertToBits(const DImage& img, uint8 threshold) {
  return convertToBitsHelper(img, threshold);
}

string getStringArray(const unsigned char* output, size_t size, string name) {
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

string getBitmapString(const unsigned char* output, int realWidth, int width, int height, string name) {
  size_t outSize = width * height;
  if (outSize == 0) {
    return "";
  }

  string pngName = "png_" + name;
  std::stringstream ss;
  ss << getStringArray(output, outSize, pngName);

  // get full structs
  string bmpName("bmp_");
  bmpName.append(name);
  string picName("pic_");
  picName.append(name);
  ss << "const Bitmap " << bmpName << "(" << pngName << ", "
    << (width * 8) << ", " << height << ");\n"
    "const Picture " << picName << "(" << bmpName << ", 0, 0, "
    << realWidth << ", " << height << ");\n\n";

  return ss.str();
}

bool appendToFile(string filepath, const string& text) {
  if (text.empty()) {
    return true;
  }
  fstream headerFile(filepath, std::ios_base::out | std::ios_base::app);
  if (!headerFile.is_open()) {
    return false;
  }
  headerFile << text;
  headerFile.close();
  return true;
}

DVector<string> readFromFile(string filepath)
{
  fstream imgfile(filepath, std::ios_base::in);
  if (!imgfile.is_open()) {
    return {};
  }
  DVector<string> list;
  string str;
  while (!imgfile.eof()) {
    std::getline(imgfile, str);
    if (!str.empty()) {
      list.push(str);
    }
  }
  imgfile.close();
  return list;
}

filesystem::path getAbsolutePath(const char* strPath) {
  auto absPath = filesystem::path(strPath).lexically_normal();
  if (absPath.is_relative()) {
    if (absPath.wstring().front() == filesystem::path::preferred_separator)
      absPath = (filesystem::current_path() += absPath);
    else
      absPath = filesystem::current_path() / absPath;
  }
  return absPath.lexically_normal();
}

int main(int count, const char** args)
{
  if (count != 3) {
    cout << "png2hex - Convert PNG images to PROGMEM HEX arrays for Arduino.\n"
      "Usage: png2hex <path to imglist.txt> <path to output dir>\n" << endl;
    return 0;
  }

  auto imagelistPath = getAbsolutePath(args[1]);

  auto outputPath = getAbsolutePath(args[2]);

  auto isf = filesystem::is_character_file(imagelistPath);
  auto isdir = filesystem::is_directory(outputPath);


  if (!filesystem::exists("imglist.txt")) {
    const char helpText[] = R"(
This program read `imglist.txt` which contains a list of image names. It converts
the images into PROGMEM arrays of HEX values suitable for Arduino projects.

Run example:
>png2hex [<path for generated files>]

Structure shall look like:
-root
|-png2hex.exe
|-imglist.txt
|-filepath
 `-img1.png
|-img2.png
`-fontpic.png

imglist.txt:
  filepath/img1.png -t200
  img2.png -t128\
  fontpic.png -f"

imglist.txt flags:
-t128  flag with a following value of the threshold after the image path.
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
    cout << helpText;
    return 1;
  }

  if (count != 2) {
    cout << "Usage: png2hex FILEPATH\n"
      "FILEPATH is a name of two autogenerated files: FILEPATH.h and FILEPATH.cpp";
    return 1;
  }

  auto list = readFromFile("imglist.txt");
  if (list.empty()) {
    cout << "Unable to read `imglist.txt` or file is empty.\n";
    return 1;
  }

  DString headerName = args[1];
  headerName += ".h";
  DString cppName = args[1];
  cppName += ".cpp";
  filesystem::remove(headerName.data());
  filesystem::remove(cppName.data());

  string includes = "#pragma once\n"
                    "#include \"Picture.h\"\n\n";
  appendToFile(headerName.data(), includes);

  includes = "#include \"";
  includes += filesystem::path(headerName.data()).filename().string();
  includes += '"';
  includes += R"(
#ifdef ARDUINO
#include <avr/pgmspace.h>
#endif

)";
  appendToFile(cppName.data(), includes);

  size_t totalNumberOfBytes = 0;

  for (DString command : list)
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
    if (!img.load(command.data())) {
      cout << "Unable to read image `" << command.data() << "`. Skipped." << endl;
      continue;
    }
    cout << (isFont ? "Font" : "Image") << " `" << command.data() << "` read." << endl;

    command.remove(".png");

    if (isFont) {
      FontInfo fi = readFontInfo(img, threshold);
      totalNumberOfBytes += fi.output.size().square() + fi.offsetsSize;
      string bitmapArray = getBitmapString(fi.output.raw(), img.size().width(), fi.output.size().width(), fi.output.size().height(), command.data());
      DString offsetName = "font_offsets_" + command;
      string offsetsArray = getStringArray(fi.offsetsData, fi.offsetsSize, offsetName.data());
      stringstream ss;
      ss << "// Each offset value contains " << int(FontInfo::OFFSET_BITS) << " bits. Use `ExtIntArray` to read.\n" << offsetsArray;
      offsetsArray = std::move(ss.str());
      if (!appendToFile(cppName.data(), offsetsArray)) {
        cout << "Unable to write to file `" << cppName.data() << "`." << endl;
        return 1;
      }
      if (!appendToFile(cppName.data(), bitmapArray)) {
        cout << "Unable to write to file `" << cppName.data() << "`." << endl;
        return 1;
      }
      DString structs =
        "extern const Bitmap bmp_" + command +
        ";\nextern const Picture pic_" + command +
        ";\nextern const uint8_t font_offsets_" + command + "[];\n\n";
      if (!appendToFile(headerName.data(), structs.data())) {
        cout << "Unable to write to file `" << headerName.data() << "`." << endl;
        return 1;
      }
    }
    else {
      DBiArray<unsigned char> output = convertToBits(img, threshold);
      totalNumberOfBytes += output.size().square();
      string array = getBitmapString(output.raw(), img.size().width(), output.size().width(), output.size().height(), command.data());
      if (!appendToFile(cppName.data(), array)) {
        cout << "Unable to write to file `" << cppName.data() << "`." << endl;
        return 1;
      }
      DString structs = 
        "extern const Bitmap bmp_" + command + 
        ";\nextern const Picture pic_" + command + ";\n\n";
      if (!appendToFile(headerName.data(), structs.data())) {
        cout << "Unable to write to file `" << headerName.data() << "`." << endl;
        return 1;
      }
    }
  }
  cout << "Generated `" << headerName.data() << "`." << endl;
  cout << "Generated `" << cppName.data() << "`." << endl;
  cout << "Total PROGMEM bytes used:" << totalNumberOfBytes << endl;
  cout << "Done." << endl;
  return 0;
}