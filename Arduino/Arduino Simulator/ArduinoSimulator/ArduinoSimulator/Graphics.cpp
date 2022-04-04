#include "Graphics.h"

static constexpr uint8_t BITS_IN_BYTE = 8;

// [min, max]
static bool isOutOfRange(int what, int min, int max)
{
  return what < min || what > max;
}

static bool isOutOfSize(Position what, Size size)
{
  return isOutOfRange(what.x, 0, size.width) || isOutOfRange(what.y, 0, size.height);
}

void Graphics::init(Buffer buffer)
{
  buf = buffer;
}

void Graphics::clear()
{
  memset(buf.data, 0, (buf.width * buf.height / BITS_IN_BYTE));
}

void Graphics::drawPixel(bool active, Position pos)
{
  if (isOutOfSize(pos, buf))
    return;
  uint8_t &b = buf.data[pos.y / BITS_IN_BYTE * buf.width + pos.x];
  char mask = 1 << pos.y % BITS_IN_BYTE;
  b &= ~mask;
  b |= (active * mask);
}

void Graphics::drawHLine(Position startPos, int size)
{
  if (isOutOfRange(startPos.y, 0, buf.height))
    return;
  if (startPos.x < 0)
  {
    size += startPos.x;
    startPos.x = 0;
  }
  if (startPos.x + size > buf.width)
  {
    size = buf.width - startPos.x;
  }
  if (size < 0)
    return;

  uint8_t* b = buf.data + startPos.y / BITS_IN_BYTE * buf.width + startPos.x;
  char mask = 1 << startPos.y % BITS_IN_BYTE;
  while (size--)
  {
    *b &= ~mask;
    *b |= mask;
    ++b;
  }
}

void Graphics::drawVLine(Position startPos, int size)
{
  if (startPos.x < 0)
  {
    size += startPos.x;
    startPos.x = 0;
  }
  if (startPos.x + size > buf.width)
  {
    size = buf.width - startPos.x;
  }
  if (size <= 0)
    return;

  uint8_t* b = buf.data + startPos.y / BITS_IN_BYTE * buf.width + startPos.x;
  char mask = 1 << startPos.y % BITS_IN_BYTE;
  while (size--)
  {
    *b &= ~mask;
    *b |= mask;
    ++b;
  }
}

void Graphics::drawPicture(Picture pic, Position pos)
{
  // if the picture is out of visible area, then do not draw.
  if (!adjustSize(pic.x, pic.width, pos.x, buf.width) ||
    !adjustSize(pic.y, pic.height, pos.y, buf.height))
    return;

  // preparatory calculations
  int picPreBits = BITS_IN_BYTE - pic.x % BITS_IN_BYTE;
  int picPostBits = (pic.x + pic.width) % BITS_IN_BYTE;
  int preBitsShift = 0;
  if (picPreBits > pic.width)
  {
    preBitsShift = picPreBits - pic.width;
    picPreBits = pic.width;
    picPostBits = 0;
  }
  const int picWholeBytes = (pic.width - picPreBits - picPostBits) / BITS_IN_BYTE;
  const int bmpWidth = pic.bmp->width / BITS_IN_BYTE;
  const uint8_t* bmpPos = pic.bmp->data + pic.x / BITS_IN_BYTE + pic.y * bmpWidth;
  uint8_t* bufPos = buf.data + pos.x + pos.y / BITS_IN_BYTE * buf.width;
  int y = pos.y;
  int picPreRows = BITS_IN_BYTE - pos.y % BITS_IN_BYTE;
  int picPostRows = (pos.y + pic.height) % BITS_IN_BYTE;
  if (picPreRows > pic.height)
  {
    picPreRows = pic.height;
    picPostRows = 0;
  }
  const int picWholeRows = (pic.height - picPreRows - picPostRows) / BITS_IN_BYTE;
  // fill buffer
  drawLines(bmpPos, bmpWidth, picPreRows, picPreBits, picWholeBytes, picPostBits, preBitsShift, bufPos, y);
  y += picPreRows;
  bmpPos += bmpWidth * picPreRows;
  bufPos += buf.width;
  const int wholeBmpWidth = bmpWidth * BITS_IN_BYTE;
  int i = picWholeRows;
  while (i--)
  {
    drawLines(bmpPos, bmpWidth, BITS_IN_BYTE, picPreBits, picWholeBytes, picPostBits, preBitsShift, bufPos, y);
    y += BITS_IN_BYTE;
    bmpPos += wholeBmpWidth;
    bufPos += buf.width;
  }
  drawLines(bmpPos, bmpWidth, picPostRows, picPreBits, picWholeBytes, picPostBits, preBitsShift, bufPos, y);
}

template<class F>
void readUTF8string(std::string text, F func)
{
  // 1 byte 0XXXXXXX
  // 2 byte 110XXXXX 10XXXXXX
  // 3 byte 1110XXXX 10XXXXXX 10XXXXXX
  // 4 byte 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
  static constexpr char auxMask = 0b00111111;
  static constexpr char masks[] = {
    0b10000000,
    0b11100000,
    0b11110000,
    0b11111000
  };

  const char* it = text.data();
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

void Graphics::drawText(std::string text, Position pos, const Font& font)
{
  readUTF8string(std::move(text), [&](int code) {
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

int Graphics::calculateTextWidth(std::string text, const Font& font)
{
  int width = 0;
  readUTF8string(std::move(text), [&](int code) {
    width += (code == int(' ')) ? font.getSpaceWidth() :
      font.getCharWidth(code) + font.getCharSpaceWidth();
    });
  return width;
}

void Graphics::drawBits(uint8_t byte, uint8_t bitCount, uint8_t* buf, uint8_t mask, uint8_t bufBitShift)
{
  while (bitCount--)
  {
    *buf = *buf & mask | ((byte & 0x80) >> bufBitShift);
    byte <<= 1;
    ++buf;
  }
}

void Graphics::drawLine(const uint8_t* bytes, int preBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y)
{
  const uint8_t bufBitShift = 7 - y % BITS_IN_BYTE;
  const uint8_t mask = ~(0x80 >> bufBitShift);
  uint8_t byte = *(bytes) << (BITS_IN_BYTE - preBits - preBitsShift);
  drawBits(byte, preBits, buf, mask, bufBitShift);
  buf += preBits;
  ++bytes;
  while (wholeBytes--)
  {
    drawBits(*(bytes), BITS_IN_BYTE, buf, mask, bufBitShift);
    buf += BITS_IN_BYTE;
    ++bytes;
  }
  drawBits(*(bytes), postBits, buf, mask, bufBitShift);
}

void Graphics::drawLines(const uint8_t* bytes, int bmpWidth, int lineCount, int picPreBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y)
{
  while (lineCount--)
  {
    drawLine(bytes, picPreBits, wholeBytes, postBits, preBitsShift, buf, y++);
    bytes += bmpWidth;
  }
}

// return `false` if it is no sense to draw, because the picture is out of screen bound,
// return `true` otherwise.
bool Graphics::adjustSize(int& picPos, int& picSize, int& bufPos, int bufSize)
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