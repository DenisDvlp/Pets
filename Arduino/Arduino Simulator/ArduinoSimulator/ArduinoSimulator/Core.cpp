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
public:
  Position pos;
  virtual int size() = 0;
  virtual const PicPos& operator[](int i) = 0;
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
  int size() override { return ::size(pics); }
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

}

void drawSprite(Graphics* g, Sprite& sprite) {
  for (int i = 0; i < sprite.size(); i++)
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
  w.pos = { 0, 0 };
  switch (button) {
  case Controller::BUTTON_X:
    drawSprite(graphics, w);
    break;
  case Controller::BUTTON_Y:
  {
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