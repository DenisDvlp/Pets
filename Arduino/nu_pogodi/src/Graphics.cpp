#include "Graphics.hpp"
#include "stl.hpp"
#ifdef ARDUINO
#include "Function.hpp"
#endif

#ifdef _WIN32
#define pgm_read_byte(ptr) uint8_t{*(ptr)}
#endif // _WIN32

static constexpr uint8_t BITS_IN_BYTE = 8;

void Graphics::init(Buffer buffer)
{
  buf = buffer;
}

void Graphics::clear()
{
  memset(buf.data, 0, (buf.width * buf.height / BITS_IN_BYTE));
}

// [min, max)
static bool isOutOfRange(int what, int min, int max)
{
  return what < min || what >= max;
}

static bool isOutOfSize(Position what, Size size)
{
  return isOutOfRange(what.x, 0, size.width) || isOutOfRange(what.y, 0, size.height);
}

inline uint8_t* Graphics::bufferOffset(Position pos)
{
  return buf.data + pos.y / BITS_IN_BYTE * buf.width + pos.x;
}

void Graphics::drawPixel(Position pos)
{
  if (isOutOfSize(pos, buf))
    return;
  const uint8_t mask = 1 << pos.y % BITS_IN_BYTE;
  *bufferOffset(pos) |= mask;
}

// return `false` if it is no sense to draw, because the line is out of screen bound,
// return `true` otherwise.
static bool adjustLine(int& a, int b, int& size, int bufA, int bufB)
{
  if (isOutOfRange(b, 0, bufB))
    return false;
  if (a < 0)
  {
    size += a;
    a = 0;
  }
  if (a + size > bufA)
  {
    size = bufA - a;
  }
  return (size >= 0);
}

void Graphics::drawHLine(Position startPos, int size)
{
  if (!adjustLine(startPos.x, startPos.y, size, buf.width, buf.height))
    return;

  uint8_t* b = bufferOffset(startPos);
  const uint8_t mask = 1 << startPos.y % BITS_IN_BYTE;
  while (size--)
  {
    *b |= mask;
    ++b;
  }
}

void Graphics::drawVLine(Position startPos, int size)
{
  if (!adjustLine(startPos.y, startPos.x, size, buf.height, buf.width))
    return;

  uint8_t* b = bufferOffset(startPos);
  uint8_t mask = 1 << startPos.y % BITS_IN_BYTE;
  while (size--)
  {
    *b |= mask;
    mask <<= 1;
    if (!mask)
    {
      mask = 1;
      b += buf.width;
    }
  }
}

void Graphics::drawLine(Position startPos, Position endPos)
{
  if (startPos.x > endPos.x)
  {
    swap(startPos, endPos);
  }

  int xLength = endPos.x - startPos.x + 1;
  int yLength = endPos.y - startPos.y + 1;
  int step = 1;
  const bool up = (yLength <= 0);
  if (up)
  {
    yLength = 2 - yLength;
    step = -1;
  }
  const bool vertical = (xLength < yLength);
  auto lineFunc = &Graphics::drawHLine;
  int* x = &startPos.y;
  int* y = &startPos.x;
  if (vertical)
  {
    lineFunc = &Graphics::drawVLine;
    x = &startPos.x;
    y = &startPos.y;
    swap(xLength, yLength);
    if (up)
    {
      startPos = endPos;
    }
  }

  if (yLength == 1)
  {
    (this->*lineFunc)(startPos, xLength);
    return;
  }

  const int size = xLength / yLength;
  const float tail = xLength % yLength;
  int extraPixels = 0;
  int i = 0;
  while (i < yLength)
  {
    const int extraPixel = (++i * tail / yLength + 0.5f) - extraPixels;
    extraPixels += extraPixel;
    const int len = size + extraPixel;
    (this->*lineFunc)(startPos, len);
    *x += step;
    *y += len;
  }
}


void Graphics::drawCircle(Position centerPos, int raduis)
{
  Position operator+(const Position& l, const Position& r);
  for (float i = 0; i < 90; i+=1)
  {
    const float radian = degToRad(i);
    int x = static_cast<int>(cos(radian) * raduis + 0.5f);
    int y = static_cast<int>(sin(radian) * raduis + 0.5f);
    drawPixel(centerPos + Position{x, y});
    drawPixel(centerPos + Position{-x, y});
    drawPixel(centerPos + Position{x, -y});
    drawPixel(centerPos + Position{-x, -y});
  }
}

// return `false` if it is no sense to draw, because the picture is out of screen bound,
// return `true` otherwise.
bool adjustSize(int& picPos, int& picSize, int& bufPos, int bufSize)
{
  int sizeI = bufPos + picSize;
  if (bufPos < 0)
  {
    picPos -= bufPos;
    bufPos = 0;
  }
  else if (bufPos >= bufSize)
  {
    return false;
  }

  if (sizeI > bufSize)
  {
    sizeI = bufSize;
  }
  if (sizeI <= 0)
  {
    return false;
  }
  picSize = sizeI - bufPos;
  return true;
}

void drawPictureLine(uint8_t* buf, int size, const uint8_t* bytes, int shiftRight, const int shiftLeft, bool transparent)
{
  const uint8_t clearBitMask = ~(1 << shiftLeft) | transparent * 0xFF;
  uint8_t byte = pgm_read_byte(bytes);
  while (true)
  {
    *buf &= clearBitMask;
    *buf |= ((byte >> shiftRight) & 1) << shiftLeft;
    ++buf;
    if (!--size)
      return;
    if (!shiftRight--)
    {
      shiftRight = BITS_IN_BYTE - 1;
      byte = pgm_read_byte(++bytes);
    }
  }
}

void Graphics::drawPicture(Picture pic, Position pos, bool transparent /*=false*/)
{
  // if the picture is out of visible area, then do not draw.
  if (!adjustSize(pic.x, pic.width, pos.x, buf.width) ||
    !adjustSize(pic.y, pic.height, pos.y, buf.height))
    return;
  uint8_t* b = bufferOffset(pos);
  const int bmpWidthInBytes = pic.bmp->width / BITS_IN_BYTE;
  const uint8_t* p = pic.bmp->data + pic.y * bmpWidthInBytes + pic.x / BITS_IN_BYTE;
  const int shiftRight = BITS_IN_BYTE - 1 - pic.x % BITS_IN_BYTE;
  while (pic.height--) {
    const int shiftLeft = pos.y++ % BITS_IN_BYTE;
    drawPictureLine(b, pic.width, p, shiftRight, shiftLeft, transparent);
    if (shiftLeft == BITS_IN_BYTE - 1)
    {
      b += buf.width;
    }
    p += bmpWidthInBytes;
  }
}

template<class F>
void readUTF8string(const String text, F func)
{
  // 1 byte 0XXXXXXX
  // 2 byte 110XXXXX 10XXXXXX
  // 3 byte 1110XXXX 10XXXXXX 10XXXXXX
  // 4 byte 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
  static constexpr char auxMask = 0b00111111;
  static constexpr char masks[] = {
    char(0b10000000),
    char(0b11100000),
    char(0b11110000),
    char(0b11111000)
  };

  const char* it = &*text.begin();
  const char* end = it + text.length();
  while (it != end)
  {
    for (auto mask : masks)
    {
      if (char(*it & mask) == char(mask << 1))
      {
        int code = *(it++) & ~mask;
        mask <<= 1;
        while (mask <<= 1)
        {
          code <<= 6;
          code |= *(it++) & auxMask;
        }
        func(code);
      }
    }
  }
}

void Graphics::drawText(String text, Position pos, const Font& font)
{
  readUTF8string(move(text), [&](int code) {
    if (code == int(' '))
    {
      pos.x += font.getSpaceWidth();
    }
    else
    {
      Picture pic = font.getPicture(code);
      drawPicture(pic, pos);
      pos.x += pic.width + font.getCharSpaceWidth();
    }
    });
}

int Graphics::calculateTextWidth(String text, const Font& font)
{
  int width = 0;
  readUTF8string(move(text), [&](int code) {
    width += (code == int(' ')) ? font.getSpaceWidth() :
      font.getCharWidth(code) + font.getCharSpaceWidth();
    });
  return width;
}
