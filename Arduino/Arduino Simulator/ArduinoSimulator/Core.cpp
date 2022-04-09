#include "Core.h"
#include "FontCirillic.h"
#include "Images.h"
#include "Sprite.h"
#include "Animation.h"

template<typename T, int S>
constexpr int size(T(&)[S]) { return S; }

class Wolf : public Sprite {
private:
  PicPos pics[3] = {
    { pic_w_body, {0, 0} },
    { pic_w_lleg, {7, 40} },
    { pic_w_rleg, {34, 35} },
  };
  int numberOfPics() const override { return ::size(pics); }
  const PicPos& getPic(int i) const override { return pics[i]; }
  void onDraw(Graphics* g) override
  {
    g->drawHLine({ pos.x + 27, pos.y + 40 }, 7);
  }
};

class Barn : public Sprite {
private:
  PicPos pics[2] = {
    { pic_dline, { 11, 11 } },
    { pic_dline, { 11, 30 } },
  };
  int numberOfPics() const override { return ::size(pics); }
  const PicPos& getPic(int i) const override { return pics[i]; }
  void onDraw(Graphics* g) override
  {
    g->drawHLine({ pos.x + -4, pos.y + 11 }, 16);
    g->drawHLine({ pos.x + -4, pos.y + 30 }, 16);
  }
};

class Chicken : public Sprite, public FrameAnimation {
private:
  const Picture pics[2] = {
    Picture(bmp_chicken, 0, 0, 11, 11),
    Picture(bmp_chicken, 11, 0, 11, 11),
  };
  void onDraw(Graphics* g) override
  {
    g->drawPicture(pics[currentFrame()], pos);
  }
public:
  Chicken() : FrameAnimation(2, 1000)
  {
    start();
  }
};

class Egg : public Sprite, public FrameAnimation {
private:
  const Picture pics[4] = {
    Picture(bmp_eggs, 0, 0, 7, 7),
    Picture(bmp_eggs, 7, 0, 7, 7),
    Picture(bmp_eggs, 14, 0, 7, 7),
    Picture(bmp_eggs, 21, 0, 7, 7),
  };
  void onDraw(Graphics* g) override
  {
    g->drawPicture(pics[currentFrame()], pos, true);
  }
public:
  Egg() : FrameAnimation(4, 700)
  {
    start();
  }
};

class EggRolling {
private:
  ValueAnimation<Position> animPos, animPos2;
  Animation* anims[2] = {
    &animPos, &animPos2
  };
  AnimationSequence as;
public:
  Egg egg;
  EggRolling() :
    animPos(egg.pos, { 10, 5 }, { 30, 15 }, 2000, 1),
    animPos2(egg.pos, { 30, 15 }, { 30, 60 }, 2000, 1),
    as(anims, size(anims))
  {
    egg.start();
    as.start();
  }
  void update(Graphics* g)
  {
    as.update();
    egg.draw(g);
  }
};

Position operator+(const Position& l, const Position& r) {
  return { l.x + r.x, l.y + r.y };
}
Position operator-(const Position& l, const Position& r) {
  return { l.x - r.x, l.y - r.y };
}
Position operator*(const Position& l, float r) {
  return { static_cast<int>(l.x * r), static_cast<int>(l.y * r) };
}
Position operator*(float l, const Position& r) {
  return r * l;
}

class Text : public Sprite {
private:
public:
  FontCirillic font;
  std::string text;
private:
  void onDraw(Graphics* g) override
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

void Stage(Graphics* graphics)
{
  static Wolf w;
  static Chicken c1, c2;
  static Barn b;
  static Text text;
  static EggRolling egg;

  text.text = "Счёт: 123";
  text.pos = { 70, 0 };
  text.draw(graphics);

  c1.draw(graphics);

  c2.pos.y = 19;
  c2.draw(graphics);

  b.draw(graphics);

  w.pos = { 32, 10 };
  w.draw(graphics);

  egg.update(graphics);
}

void Core::update()
{
  graphics->clear();
  Stage(graphics);
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
