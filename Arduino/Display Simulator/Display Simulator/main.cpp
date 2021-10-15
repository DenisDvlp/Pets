#include "Picture.h"
#include <iostream>

using namespace std;

constexpr int W = 64;
constexpr int H = 16;
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

void drawBytes(const uint8_t*& bytes, int byteCount, uint8_t* &buf, uint8_t mask, uint8_t bufBitShift)
{
  uint8_t byte = *bytes;
  while (byteCount--)
  {
    uint8_t* bufEnd = buf + BITS_IN_BYTE;
    while (buf != bufEnd)
    {
      *buf = *buf & mask | ((byte & 0x80) >> bufBitShift);
      byte <<= 1;
      ++buf;
    }
    ++bytes;
    byte = *bytes;
  }
}

void drawBits(uint8_t byte, uint8_t bitCount, uint8_t* &buf, uint8_t mask, uint8_t bufBitShift)
{
  while (bitCount--)
  {
    *buf = *buf & mask | ((byte & 0x80) >> bufBitShift);
    byte <<= 1;
    ++buf;
  }
}

void drawLine(const uint8_t* bytes, int preBits, int wholeBytes, int postBits, uint8_t* buf, int y)
{
  const uint8_t bufBitShift = 7 - y % BITS_IN_BYTE;
  const uint8_t mask = ~(0x80 >> bufBitShift);  
  // preBits always > 0
  const uint8_t byte = *bytes << (BITS_IN_BYTE - preBits);
  drawBits(byte, preBits, buf, mask, bufBitShift);
  ++bytes;
  drawBytes(bytes, wholeBytes, buf, mask, bufBitShift);
  drawBits(*bytes, postBits, buf, mask, bufBitShift);
}

void adjustSize(int& picI, int& picSize, int& bufI, int& bufSize)
{
  if (bufI < 0)
  {
    picI -= bufI;
    picSize += bufI;
    bufI = 0;
  }
  const int delta = bufSize - bufI - picSize;
  if (delta < 0)
  {
    picSize += delta;
  }
};

void drawPicture(Picture pic, Buffer& buf, Position pos)
{
  adjustSize(pic.x, pic.width, pos.x, buf.width);
  adjustSize(pic.y, pic.height, pos.y, buf.height);

  const int picPreBits = BITS_IN_BYTE - pic.x % BITS_IN_BYTE;
  const int picPostBits = (pic.x + pic.width) % BITS_IN_BYTE;
  const int picWholeBytes = (pic.width - picPreBits - picPostBits) / BITS_IN_BYTE;
  const int bmpWidth = pic.bmp->width / BITS_IN_BYTE;
  const uint8_t* bmpPos = pic.bmp->data + pic.x / BITS_IN_BYTE + pic.y * bmpWidth;
  const int endRaw = pic.height + pos.y;
  uint8_t* bufPos = buf.data + pos.x + pos.y / BITS_IN_BYTE * buf.width;
  int y = pos.y;
  int picPreRows = BITS_IN_BYTE - pic.y % BITS_IN_BYTE;
  int picPostRows = (pic.y + pic.height) % BITS_IN_BYTE;
  int picWholeRows = (pic.height - picPreRows - picPostRows) / BITS_IN_BYTE;
  while (picPreRows--)
  {
    drawLine(bmpPos, picPreBits, picWholeBytes, picPostBits, bufPos, y++);
    bmpPos += bmpWidth;
  }
  bufPos += buf.width;
  for (size_t i = 0; i < picWholeRows; ++i)
  {
    for (size_t i = 0; i < BITS_IN_BYTE; ++i)
    {
      drawLine(bmpPos, picPreBits, picWholeBytes, picPostBits, bufPos, y++);
      bmpPos += bmpWidth;
    }
    bufPos += buf.width;
  }
  while (picPostRows--) {
    drawLine(bmpPos, picPreBits, picWholeBytes, picPostBits, bufPos, y++);
    bmpPos += bmpWidth;
  }
}

Buffer buffer(buf, W, H);
Picture pic_2(&bmp_1, 3, 3, 13, 5);

void main()
{
  Position pos(4, 2);
  drawPicture(pic_2, buffer, pos);
	display();
}