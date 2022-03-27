#include "Graphics.h"

static constexpr uint8_t BITS_IN_BYTE = 8;

void Graphics::init(Buffer buffer)
{
  buf = buffer;
}

void Graphics::clear()
{
  memset(buf.data, 0, (buf.width * buf.height / BITS_IN_BYTE));
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

// 1 byte 0XXXXXXX
// 2 byte 110XXXXX 10XXXXXX
// 3 byte 1110XXXX 10XXXXXX 10XXXXXX
// 4 byte 11110XXX 10XXXXXX 10XXXXXX 10XXXXXX
int readUTF8Code(const char*& it) {
  int code = -1;

  // 1 byte
  if ((it[0] & 0b10000000) == 0b00000000)
  {
    code = it[0];
    it += 1;
  }
  // 2 bytes
  else if ((it[0] & 0b11100000) == 0b11000000)
  {
    code = (it[0] & 0b00011111) << 6 | (it[1] & 0b00111111);
    it += 2;
  }
  // 3 bytes
  else if ((it[0] & 0b11110000) == 0b11100000)
  {
    code = (it[0] & 0b00001111) << 12 | (it[1] & 0b00111111) << 6 | (it[2] & 0b00111111);
    it += 3;
  }
  // 4 bytes
  else if ((it[0] & 0b11111000) == 0b11110000)
  {
    code = (it[0] & 0b00000111) << 18 | (it[1] & 0b00111111) << 12 | (it[2] & 0b00111111) << 6 | (it[3] & 0b00111111);
    it += 4;
  }

  return code;
}

void Graphics::drawText(std::string text, Position pos, const Font& font)
{
  size_t i = 0;
  const char* it = text.data();
  const char* end = it + text.length();
  while (it != end)
  {
    int code = readUTF8Code(it);
    if (code == int(' '))
    {
      pos.x += font.getSpaceWidth();
      continue;
    }
    Picture pic = font.getPicture(code);
    drawPicture(pic, pos);
    pos.x += pic.width + font.getCharSpaceWidth();
  }
}

int Graphics::calculateTextWidth(std::string text, const Font& font)
{
  size_t i = 0;
  int width = 0;
  while (i < text.length())
  {
    const bool isAscii = text[i] & 0b10000000;
    if (text[i] == ' ') {
      width += font.getSpaceWidth();
      ++i;
      continue;
    }
    char16_t c = char16_t(text[i] & 0b00011111) << 6 | (text[i + 1] & 0b00111111);
    width += font.getCharWidth(c) + font.getCharSpaceWidth();
    i += 2;
  }
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
bool Graphics::adjustSize(int& picI, int& picSize, int& bufI, int& bufSize)
{
  int sizeI = bufI + picSize;
  if (bufI < 0)
  {
    picI -= bufI;
    bufI = 0;
  }
  else if (bufI >= bufSize)
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
  picSize = sizeI - bufI;
  return true;
}