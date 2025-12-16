#pragma once
#include "Picture.hpp"
#include "Graphics.hpp"

#ifdef ARDUINO
#else
using namespace std;
#endif


struct PicPos {
  Picture pic;
  Position pos;
};

class Sprite {
private:
  Size size;
public:
  Position pos;
  bool show = true;
  virtual int numberOfPics() const { return 0; };
  virtual const PicPos& getPic(int i) const { return *static_cast<const PicPos*>(nullptr); };
  void draw(Graphics* g) {
    if (show)
    {
      for (int i = 0; i < numberOfPics(); ++i)
      {
        const PicPos& picPos = getPic(i);
        const Position pos = {
          picPos.pos.x + this->pos.x,
          picPos.pos.y + this->pos.y
        };
        g->drawPicture(picPos.pic, pos);
      }
      onDraw(g);
    }
  }
  virtual void onDraw(Graphics* g) {}

  void calcSize() {
    const PicPos& pp = getPic(0);
    int minW = pp.pos.x;
    int maxW = pp.pos.x + pp.pic.width;
    int minH = pp.pos.y;
    int maxH = pp.pos.y + pp.pic.height;
    for (int i = 1; i < numberOfPics(); ++i)
    {
      const PicPos& pp = getPic(i);
      minW = min(minW, pp.pos.x);
      maxW = max(maxW, pp.pos.x + pp.pic.width);
      minH = min(minH, pp.pos.y);
      maxH = max(maxH, pp.pos.y + pp.pic.height);
    }
    size.width = maxW - minW;
    size.height = maxH - minH;
  }
};
