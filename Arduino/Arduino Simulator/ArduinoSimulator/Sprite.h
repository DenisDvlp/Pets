#pragma once
#include "Picture.h"
#include "Graphics.h"

struct PicPos {
  Picture pic;
  Position pos;
};

class Sprite {
private:
  Size size;
public:
  Position pos;
  virtual int numberOfPics() { return 0; };
  virtual const PicPos& getPic(int i) { return *static_cast<const PicPos*>(nullptr); };
  void drawPics(Graphics* g) {
    for (int i = 0; i < numberOfPics(); ++i)
    {
      const PicPos& picPos = getPic(i);
      const Position pos = {
        picPos.pos.x + this->pos.x,
        picPos.pos.y + this->pos.y
      };
      g->drawPicture(picPos.pic, pos);
    }
  }
  virtual void draw(Graphics* g) {}

  void calcSize() {
    const PicPos& pp = getPic(0);
    int minW = pp.pos.x;
    int maxW = pp.pos.x + pp.pic.width;
    int minH = pp.pos.y;
    int maxH = pp.pos.y + pp.pic.height;
    for (int i = 1; i < numberOfPics(); ++i)
    {
      const PicPos& pp = getPic(i);
      minW = std::min(minW, pp.pos.x);
      maxW = std::max(maxW, pp.pos.x + pp.pic.width);
      minH = std::min(minH, pp.pos.y);
      maxH = std::max(maxH, pp.pos.y + pp.pic.height);
    }
    size.width = maxW - minW;
    size.height = maxH - minH;
  }
};