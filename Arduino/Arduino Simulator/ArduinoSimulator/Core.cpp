#include "Core.h"
#include "FontCirillic.h"
#include "Images.h"
#include "Sprite.h"

template<typename T, int S>
constexpr int size(T(&)[S]) { return S; }

class Wolf : public Sprite {
private:
  PicPos pics[3] = {
    { pic_w_body, {0, 0} },
    { pic_w_lleg, {7, 40} },
    { pic_w_rleg, {34, 35} },
  };
public:
  int frame = 0;
  int numberOfPics() override { return ::size(pics); }
  const PicPos& getPic(int i) override { return pics[i]; }
  void draw(Graphics* g) override
  {
    drawPics(g);
    g->drawHLine({ pos.x + 27, pos.y + 40 }, 7);
    if (frame)
    {
      g->drawPicture(pic_w_basket, { pos.x , pos.y + 6 });
    }
  }
};

class Barn : public Sprite {
private:
  PicPos pics[2] = {
    { pic_dline, { 11, 11 } },
    { pic_dline, { 11, 30 } },
  };
public:
  int numberOfPics() override { return ::size(pics); }
  const PicPos& getPic(int i) override { return pics[i]; }
  void draw(Graphics* g) override
  {
    drawPics(g);
    g->drawHLine({ pos.x + -4, pos.y + 11 }, 16);
    g->drawHLine({ pos.x + -4, pos.y + 30 }, 16);
  }
};

class Chicken : public Sprite {
private:
public:
  int frame = 0;
  void draw(Graphics* g) override
  {
    g->drawPicture(Picture(bmp_chicken, (frame ? 11 : 0), 0, 11, 11), pos);
  }
};

class Text : public Sprite {
private:
public:
  FontCirillic font;
  std::string text;
  void draw(Graphics* g) override
  {
    g->drawText(text, pos, font);
  }
};

void Core::init(Controller& c, Graphics& g)
{
  controller = &c;
  graphics = &g;

  // init buttons
  c.init({ this, &Core::pressDown });
}

Wolf w;
Chicken c1, c2;
Barn b;
Text text;

void Stage(Graphics* graphics)
{
  text.text = "Счёт: 123";
  text.pos = { 70, 0 };
  text.draw(graphics);

  c1.frame = c1.frame ? 0 : 1;
  c1.draw(graphics);

  c2.frame = c2.frame ? 0 : 1;
  c2.pos.y = 19;
  c2.draw(graphics);

  b.draw(graphics);

  w.frame = w.frame ? 0 : 1;
  w.pos = { 32, 10 };
  w.draw(graphics);
}

void Core::update()
{
  graphics->clear();
  //Stage(graphics);

  static int x = 0, y = 0;
  FontCirillic font;
  std::string text = "! \"#$%&'()*+,-./0123456789:;<=>?@ABCDEFGHIJKLMNOPQRSTUVWXYZ[\\]^_`abcdefghijklmnopqrstuvwxyz{|}~ЁАБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯабвгдежзийклмнопрстуфхцчшщъыьэюяё";
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
    w.draw(graphics);
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
    w.draw(graphics);
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
