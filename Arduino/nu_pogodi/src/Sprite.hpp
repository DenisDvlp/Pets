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
  const PicPos* picPos = nullptr;
  const int picNumber = 0;
  Size size;
public:
  Position pos;
  bool show = true;
  Sprite() = default;
  template<int S>
  Sprite(const PicPos(&pics)[S]) :picPos(pics), picNumber(S) {
    calcSize();
  }
  int numberOfPics() const { return picNumber; };
  virtual const PicPos& getPic(int i) const { return *static_cast<const PicPos*>(nullptr); };
  void draw(Graphics* g) {
    if (show)
    {
      for (int i = 0; i < numberOfPics(); ++i)
      {
        const PicPos& pp = picPos[i];
        const Position pos = {
          pp.pos.x + this->pos.x,
          pp.pos.y + this->pos.y
        };
        g->drawPicture(pp.pic, pos);
      }
      onDraw(g);
    }
  }
  virtual void onDraw(Graphics* g) {}

  void calcSize() {
    const PicPos& pp = picPos[0];
    int minW = pp.pos.x;
    int maxW = pp.pos.x + pp.pic.width;
    int minH = pp.pos.y;
    int maxH = pp.pos.y + pp.pic.height;
    for (int i = 1; i < picNumber; ++i)
    {
      const PicPos& pp = picPos[i];
      minW = min(minW, pp.pos.x);
      maxW = max(maxW, pp.pos.x + pp.pic.width);
      minH = min(minH, pp.pos.y);
      maxH = max(maxH, pp.pos.y + pp.pic.height);
    }
    size.width = maxW - minW;
    size.height = maxH - minH;
  }
};
