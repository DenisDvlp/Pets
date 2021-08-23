#include "Picture.h"
#include <iostream>

using namespace std;

constexpr int W = 64;
constexpr int H = 16;
uint8_t buf[W * H / 8] = { 0 };

void display() {
	for (size_t i = 0; i < H / 8; i++)
	{
		for (size_t k = 0; k < 8; k++) {
			for (size_t j = 0; j < W; j++)
			{
			  char byte = buf[i * W + j];
				cout << ((byte >> k & 1) ? "#" : " ");
			}
		cout << endl;
		}
	}
}

void SH1106_setPixel(int& picI, int& picSize, int& bufI, int& bufSize) {
  if (bufI < 0) {
    picI -= bufI;
    picSize += bufI;
    bufI = 0;
  }
  int delta = bufSize - bufI - picSize;
  if (delta < 0) {
    picSize += delta;
  }
}

void drawByte(uint8_t byte, uint8_t fromBit, uint8_t toBit, Buffer& buffer, const Position& pos)
{
  constexpr uint8_t BITS_IN_BYTE = 8;
  uint8_t* buf = buffer.data + pos.x + pos.y / BITS_IN_BYTE * buffer.width + toBit - fromBit;
  const uint8_t bufBitShift = pos.y % BITS_IN_BYTE;
  const uint8_t mask = ~(1 << bufBitShift);
  byte >>= BITS_IN_BYTE - toBit;
  while (fromBit < toBit--)
  {
    *buf = *buf & mask | ((byte & 1) << bufBitShift);
    byte >>= 1;
    --buf;
  }
}

void adjustSize(int& picI, int& picSize, int& bufI, int& bufSize)
{
  if (bufI < 0) {
    picI -= bufI;
    picSize += bufI;
    bufI = 0;
  }
  const int delta = bufSize - bufI - picSize;
  if (delta < 0) {
    picSize += delta;
  }
};

void drawPicture(Picture pic, Buffer& buf, Position pos)
{
  adjustSize(pic.x, pic.width, pos.x, buf.width);
  adjustSize(pic.y, pic.height, pos.y, buf.height);

  constexpr uint8_t BITS_IN_BYTE = 8;
  int picStartBits = pic.x % BITS_IN_BYTE;
  int picEndBits = (pic.x + pic.width) % BITS_IN_BYTE;
  int picWholeBytes = (pic.width - picStartBits - picEndBits) / BITS_IN_BYTE;
  int picBytes = picWholeBytes + bool(picStartBits) + bool(picEndBits);
  int bmpWidth = pic.bmp->width / BITS_IN_BYTE;
  const uint8_t* bmp = pic.bmp->data + pic.x / BITS_IN_BYTE + pic.y * bmpWidth;
  int deltaWidth = bmpWidth - picBytes;
  int toBit = (picWholeBytes + bool(picEndBits)) * BITS_IN_BYTE + picEndBits;

  for (int y = pos.y, endRaw = pic.height + pos.y; y < endRaw; ++y)
  {
    int _toBit = toBit;
    drawByte(*bmp++, picStartBits, BITS_IN_BYTE, buf, { pos.x, y });
    _toBit -= BITS_IN_BYTE;
    for (int i = 1, x = pos.x + BITS_IN_BYTE; i < picBytes; ++i) {
      drawByte(*bmp++, 0, _toBit % BITS_IN_BYTE, buf, { x, y });
      x += BITS_IN_BYTE;
      _toBit -= BITS_IN_BYTE;
    }
    bmp += deltaWidth;
  }
}

void SH1106_picture(const uint8_t* bmp, int bmpW, int bmpH, int picX, int picY, int picW, int picH, uint8_t* buffer, int bufX, int bufY, int bufW, int bufH)
{
  auto adjustSize = [](int& picI, int& picSize, int& bufI, int& bufSize) {
    if (bufI < 0) {
      picI -= bufI;
      picSize += bufI;
      bufI = 0;
    }
    int delta = bufSize - bufI - picSize;
    if (delta < 0) {
      picSize += delta;
    }
  };

  // Adjust sizes.
  adjustSize(picX, picW, bufX, bufW);
  adjustSize(picY, picH, bufY, bufH);

  constexpr uint8_t BITS_IN_BYTE = 8;
  const int startBitInByte = picX % BITS_IN_BYTE;
  const int startByteInBmpRow = picX / BITS_IN_BYTE;
  const int bytesInBmpWidth = bmpW / BITS_IN_BYTE;
  int startByteInBmp = startByteInBmpRow + (picY * bytesInBmpWidth);
  const int excessBitsInPicWidth = picW % BITS_IN_BYTE;
  const int bitsInPicWidthLastIncompleteByte = startBitInByte + excessBitsInPicWidth;
  const int bytesInPicWidth = (picW / BITS_IN_BYTE) + (!bitsInPicWidthLastIncompleteByte && excessBitsInPicWidth); 

  auto setPixel = [BITS_IN_BYTE](uint8_t byte, int bitX, int endBit, uint8_t* buffer, int &bufX, int bufY, int bufW) {
    while (bitX < endBit)
    {
      const bool color = (byte << bitX++ & 0x80); // read byte
      const uint8_t bits = (1 << bufY % BITS_IN_BYTE); // write byte
      uint8_t& bufByte = buffer[bufX++ + (bufY / BITS_IN_BYTE) * bufW];
      if (color)
        bufByte |= bits;
      else
        bufByte &= ~bits;
    }
  };

  auto it = bmp + startByteInBmp;
  int bitX = startBitInByte;
  auto e = it + bytesInPicWidth;

  if (bitsInPicWidthLastIncompleteByte) {
    // for each row
    for (int i = 0; i < picH; ++i, ++bufY, bufX -= picW, it += (bytesInBmpWidth - bytesInPicWidth), e += bytesInBmpWidth, bitX = startBitInByte)
    {
      // for each byte in a row
      for (; it != e; ++it, bitX = 0)
      {
        setPixel(*it, bitX, BITS_IN_BYTE, buffer, bufX, bufY, bufW);
      }
      setPixel(*it, bitX, bitsInPicWidthLastIncompleteByte, buffer, bufX, bufY, bufW);
    }
    return;
  }

  // for each row
  for (int i = 0; i < picH; ++i, ++bufY, bufX -= picW, it += (bytesInBmpWidth - bytesInPicWidth), e += bytesInBmpWidth, bitX = startBitInByte)
  {
    // for each byte in a row
    for (; it != e; ++it, bitX = 0)
    {
      setPixel(*it, bitX, BITS_IN_BYTE, buffer, bufX, bufY, bufW);
    }
  }
}


void drawPicture(const Picture& pic, const Buffer& buf, const Position& pos)
{
  SH1106_picture(pic.bmp->data, pic.bmp->width, pic.bmp->height, pic.x, pic.y, pic.width, pic.height, buf.data, pos.x, pos.y, buf.width, buf.height);
}

Picture eggsPic(&bmp_eggs, 0, 0, 32, 8);
Buffer buffer(buf, W, H);

void main()
{
  Position pos(0, 0);
  drawPicture(eggsPic, buffer, pos);
	display();
}