// png2hex.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include "DImage.h"
#include "DString.h"
#include <iostream>
#include <bitset>
#include <sstream>
#include <fstream>
#include <filesystem>

using namespace std;

DBiArray<unsigned char> convertToBits(const DImage& img) {
  static constexpr size_t BITS_IN_BYTE = 8;
  const auto imgSize = img.size();
  const int16 widthOut = (imgSize.width() / BITS_IN_BYTE +
    (imgSize.width() % BITS_IN_BYTE ? 1 : 0));

  DBiArray<unsigned char> output;
  output.size(widthOut, imgSize.height());

  std::bitset<BITS_IN_BYTE> bits;
  for (size_t i = 0, k = 0; i < imgSize.height(); i++)
  {
    for (size_t j = 0; j < imgSize.width(); ++k)
    {
      bits.reset();
      for (int k = BITS_IN_BYTE - 1; k >= 0 && j < imgSize.width(); ++j, --k)
      {
        // White and Transparent are - 0 (considered as a background),
        // otherwise - 1
        bits.set(k, img[i][j] != DColors::WHITE && img[i][j] != DColors::TRANSPARENT);
      }
      output.raw()[k] = static_cast<unsigned char>(bits.to_ulong());
    }
  }
  return output;
}

std::string getStringArray(const DBiArray<unsigned char>& output, string name) {
  static constexpr size_t HEX_IN_ROW = 12;
  static const char lookupHexTable[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
  };
  size_t outSize = output.size().square();
  if (outSize == 0) {
    return "";
  }
  std::string pngName("png_");
  pngName.append(name);
  std::string bmpName("bmp_");
  bmpName.append(name);
  std::string picName("pic_");
  picName.append(name);
  std::stringstream ss;
  ss << "static const uint8_t " << pngName <<"[" << outSize << "] PROGMEM  = { ";
  for (size_t i = 0; i < outSize; ++i)
  {
    if (i % HEX_IN_ROW == 0) {
      ss << "\n  ";
    }
    ss << "0x" << lookupHexTable[output.raw()[i] >> 4] << lookupHexTable[output.raw()[i] & 0xF] << ", ";
  }
  ss << "\n};\n"
    "static const Bitmap " << bmpName << "(" << pngName << ", "
    << (output.size().width() * 8) << ", " << output.size().height() << ");\n"
    "static const Picture " << picName << "(&" << bmpName << ");\n\n";

  return ss.str();
}

bool appendToFile(std::string filepath, std::string text) {
  if (text.empty()) {
    return true;
  }
  std::fstream headerFile(filepath, std::ios_base::out | std::ios_base::app);
  if (!headerFile.is_open()) {
    return false;
  }
  headerFile << text;
  headerFile.close();
  return true;
}

DVector<std::string> readFromFile(std::string filepath)
{
  std::fstream imgfile(filepath, std::ios_base::in);
  if (!imgfile.is_open()) {
    return {};
  }
  DVector<std::string> list;
  std::string str;
  while (!imgfile.eof()) {
    imgfile >> str;
    list.push(str);
  }
  imgfile.close();
  return list;
}

int main(int count)
{
  std::cout << "This program use pnglist.txt\n"
    "which contains a list of image names.\n"
    "For instance:\n\n\timg1.png\n\timg2.png\n\n";

  if (!std::filesystem::exists("imglist.txt")) {
    cout << "`imglist.txt` does not exist.\n";
    return 1;
  }

  auto list = readFromFile("imglist.txt");
  if (list.empty()) {
    cout << "Unable to read `imglist.txt` or file is empty.\n";
    return 1;
  }

  DString headerName = "images.gen";
  filesystem::remove(headerName.data());
  for (auto& name : list)
  {
    DImage img;
    if (!img.load(name)) {
      std::cout << "Unable to read image `" << name << "`. Skipped." << endl;
      continue;
    }
    std::cout << "Image `" << name << "` read." << endl;

    DBiArray<unsigned char> output = convertToBits(img);
    DString s = name;
    s.remove(".png");
    std::string array = getStringArray(output, s.data());
    if (!appendToFile(headerName.data(), array)) {
      std::cout << "Unable to write to file `" << headerName.data() << "`." << endl;
      return 1;
    }
  }
  std::cout << "Done." << endl;
  return 0;
}