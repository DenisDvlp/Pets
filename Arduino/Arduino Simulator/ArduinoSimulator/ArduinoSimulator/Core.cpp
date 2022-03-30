#include "Core.h"
#include "FontCirillic.h"
#include "Images.h"

template<typename T, size_t S>
constexpr size_t size(T(&)[S]) { return S; }

struct PicPos {
  Picture pic;
  Position pos;
};

class Sprite {
private:
  Size size;
public:
  Position pos;
  virtual int numberOfPics() = 0;
  virtual const PicPos& operator[](int i) = 0;
  void calcSize() {
    const PicPos& pp = operator[](0);
    int minW = pp.pos.x;
    int maxW = pp.pos.x + pp.pic.width;
    int minH = pp.pos.y;
    int maxH = pp.pos.y + pp.pic.height;
    for (int i = 1; i < numberOfPics(); ++i)
    {
      const PicPos& pp = operator[](i);
      minW = std::min(minW, pp.pos.x);
      maxW = std::max(maxW, pp.pos.x + pp.pic.width);
      minH = std::min(minH, pp.pos.y);
      maxH = std::max(maxH, pp.pos.y + pp.pic.height);
    }
    size.width = maxW - minW;
    size.height = maxH - minH;
  }
};

class Wolf : public Sprite {
private:
  PicPos pics[4] = {
    { pic_w_body, {0, 0} },
    { pic_w_lleg, {7, 40} },
    { pic_w_rleg, {34, 35} },
    { Picture(bmp_hline, 0, 0, 8, 1), { 26, 40 }},
  };
public:
  Wolf() {
    calcSize();
  }
  int numberOfPics() override { return ::size(pics); }
  const PicPos& operator[](int i) override { return pics[i]; }
};

void Core::init(Controller& c, Graphics& g)
{
  controller = &c;
  graphics = &g;

  // init buttons
  c.init({ this, &Core::pressDown });
}

void Core::update()
{
  static int x = 0;
  graphics->drawPixel(true, { x++,x });
}

void drawSprite(Graphics* g, Sprite& sprite) {
  for (int i = 0; i < sprite.numberOfPics(); i++)
  {
    const PicPos& picPos = sprite[i];
    Position pos = {
      picPos.pos.x + sprite.pos.x,
      picPos.pos.y + sprite.pos.y
    };
    g->drawPicture(picPos.pic, pos);
  }
}

void Core::pressDown(uint8_t button)
{
  static int x = 0, y = 0;
  graphics->clear();
  FontCirillic font;
  std::string text = "! \"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюяё";

  auto draw = [&]() {
    font.size = 0;
    Position pos = { x, y };
    graphics->drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 1;
    graphics->drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 2;
    graphics->drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 3;
    graphics->drawText(text, pos, font);
    pos.y += font.getCharHeight();
    font.size = 4;
    graphics->drawText(text, pos, font);
  };
  Wolf w;
  w.pos = { 32, 10 };
  switch (button) {
  case Controller::BUTTON_X:
    font.size = 0;
    graphics->drawText("Счёт: 123", { 70, 0 }, font);
    graphics->drawPicture(Picture(bmp_chicken, 0, 0, 11, 11), {0, 0});
    graphics->drawPicture(Picture(bmp_chicken, 0, 0, 11, 11), {0, 19});
    graphics->drawPicture(pic_hline, { -4, 11 });
    graphics->drawPicture(pic_hline, { -4, 30 });
    graphics->drawPicture(pic_dline, { 11, 11 });
    graphics->drawPicture(pic_dline, { 11, 30 });
    drawSprite(graphics, w);
    break;
  case Controller::BUTTON_Y:
  {
    font.size = 0;
    graphics->drawText("Счёт: 123", { 70, 0 }, font);
    graphics->drawPicture(Picture(bmp_chicken, 0, 0, 11, 11), { 0, 0 });
    graphics->drawPicture(Picture(bmp_chicken, 0, 0, 11, 11), { 0, 19 });
    graphics->drawPicture(pic_hline, { -4, 11 });
    graphics->drawPicture(pic_hline, { -4, 30 });
    graphics->drawPicture(pic_dline, { 11, 11 });
    graphics->drawPicture(pic_dline, { 11, 30 });
    drawSprite(graphics, w);
    Position pos = { w.pos.x , w.pos.y + 6 };
    graphics->drawPicture(pic_w_basket, pos);
  }
    break;
  case Controller::BUTTON_A:
    y += 10;
    draw();
    break;
  case Controller::BUTTON_B:
    y -= 10;
    draw();
    break;
  }
}
