#include "Picture.h"
#include "Images.h"
#include <iostream>

using namespace std;

constexpr int W = 128;
constexpr int H = 64;
uint8_t buf[W * H / 8] = { 0 };

void display() {
	for (size_t i = 0; i < H / 8; i++)
	{
		for (size_t k = 0; k < 8; k++)
    {
			for (size_t j = 0; j < W; j++)
			{
			  char byte = buf[i * W + j];
				cout << ((byte >> k & 1) ? "#" : ".");
			}
		cout << endl;
		}
	}
}

static constexpr uint8_t BITS_IN_BYTE = 8;

// return `false` if it is no sense to draw, because the picture is out of screen bound,
// return `true` otherwise.
bool adjustSize(int& picI, int& picSize, int& bufI, int& bufSize)
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
};

void drawBits(uint8_t byte, uint8_t bitCount, uint8_t* buf, uint8_t mask, uint8_t bufBitShift)
{
  while (bitCount--)
  {
    *buf = *buf & mask | ((byte & 0x80) >> bufBitShift);
    byte <<= 1;
    ++buf;
  }
}

void drawLine(const uint8_t* bytes, int preBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y)
{
  const uint8_t bufBitShift = 7 - y % BITS_IN_BYTE;
  const uint8_t mask = ~(0x80 >> bufBitShift);
  uint8_t byte = *bytes << (BITS_IN_BYTE - preBits - preBitsShift);
  drawBits(byte, preBits, buf, mask, bufBitShift);
  buf += preBits;
  ++bytes; 
  while (wholeBytes--)
  {
    drawBits(*bytes, BITS_IN_BYTE, buf, mask, bufBitShift);
    buf += BITS_IN_BYTE;
    ++bytes;
  }
  drawBits(*bytes, postBits, buf, mask, bufBitShift);
}

void drawLines(const uint8_t* bytes, int bmpWidth, int lineCount, int picPreBits, int wholeBytes, int postBits, int preBitsShift, uint8_t* buf, int y)
{
  while (lineCount--)
  {
    drawLine(bytes, picPreBits, wholeBytes, postBits, preBitsShift, buf, y++);
    bytes += bmpWidth;
  }
}

void drawPicture(Picture pic, Buffer& buf, Position pos)
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

Buffer buffer(buf, W, H);

void main()
{
  Position pos(0, 0);
  srand(time(0));
  drawPicture(pic_nupogodi, buffer, {0,20});
	display();
}