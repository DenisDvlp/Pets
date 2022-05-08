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
    g->drawPicture(pic_w_basket, { pos.x, pos.y + 6 });
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
    g->drawPicture(pics[frame], pos);
  }
public:
  int frame = 0;
  Chicken() : FrameAnimation(2, 1000) {}
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
    g->drawPicture(pics[getCurrentFrame()], pos, true);
  }
public:
  Egg() : FrameAnimation(4, 700) {}
};

class EggRolling : public Sprite, public Animation {
private:
  Chicken chicken;
  Egg egg;
  FrameAnimation fa;
  ValueAnimation<Position> animPos, animPos2;
  ValueAnimation<bool> animShow;
  Animation* anims[4] = {
    &fa, &animShow, &animPos, &animPos2
  };
  SequenceAnimation sa;
public:
  Position pos;
  EggRolling() :
    fa(2, 300, 3),
    animPos(egg.pos, { 10, 5 }, { 30, 15 }, 1500, 1),
    animPos2(egg.pos, { 30, 15 }, { 30, 60 }, 1000, 1),
    animShow(egg.show, false, true, 0, 1),
    sa(anims, ::size(anims), 1) {
    egg.show = false;
    egg.pos = { 10, 5 };
  }
  void setPosition(Position pos)
  {
  }
  void onStart(milliseconds now) override
  {
    sa.start(now);
    egg.start(now);
  }
  void onStop() override
  {
    sa.stop();
    chicken.frame = 0;
    egg.show = false;
    egg.stop();
  }
  void onUpdate(milliseconds now)
  {
    sa.update(now);
    chicken.frame = fa.getCurrentFrame();
    egg.update(now);
  }
  void onDraw(Graphics* g)
  {
    chicken.draw(g);
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
  String text;
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
  //static Wolf w;
  //static Chicken c1, c2;
  //static Barn b;
  //static Text text;
  //static EggRolling egg;

  //milliseconds now = millis();

  //text.text = "Счёт: 123";
  //text.pos = { 70, 0 };
  //text.draw(graphics);

  //c2.pos.y = 19;
  //c2.start(now);
  //c2.update(now);
  //c2.draw(graphics);

  //b.draw(graphics);

  //w.pos = { 32, 10 };
  //w.draw(graphics);

  //egg.update(now);
  //egg.draw(graphics);
  static Position start = { 30, 30 };
  static int R = 25;
  static int A = 19;
  Position end = { start.x + static_cast<int>(cos(A * 3.14 / 180) * R), start.y + static_cast<int>(sin(A * 3.14 / 180) * R) };
  A += 1;
  if (A == 360) A = 0;
  graphics->drawLine(start, end);
  graphics->drawLine({ 20,0 }, { 11,11 });
}

void Core::update()
{
  graphics->clear();
  Stage(graphics);
}

void Core::pressDown(uint8_t button)
{
  switch (button) {
  case Controller::BUTTON_X:
    break;
  case Controller::BUTTON_Y:
    break;
  case Controller::BUTTON_A:
    break;
  case Controller::BUTTON_B:
    break;
  }
}
