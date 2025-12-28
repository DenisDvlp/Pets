#include "Core.hpp"
#include "FontCirillic.hpp"
#include "Images.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "stl.hpp"

class Wolf : public Position {
  Picture currentBasket{ pic_basket_up_down };
  bool basketRight = true;
public:
  Wolf() {
    basketLeftUp();
    currentBasket.width = pic_basket_up_down.width / 2;
  }
  void basketLeftDown() {
    currentBasket.x = currentBasket.width;
    basketRight = false;
  }
  void basketLeftUp() {
    currentBasket.x = 0;
    basketRight = false;
  }
  void basketRightDown() {
    currentBasket.x = currentBasket.width;
    basketRight = true;
  }
  void basketRightUp() {
    currentBasket.x = 0;
    basketRight = true;
  }
  void draw(Graphics* g) {
    g->drawPicture(pic_wolf_body, *this, basketRight);
    g->drawPicture(currentBasket, {x - 7 + 30 * basketRight, y + 6}, basketRight);
  }
};

class Background {
public:
  void draw(Graphics* g) {
    g->drawPicture(pic_background, { 0, 0 });
  }
};

class Egg: public Position, public AnimatedPicture {
  static const Picture pics[4];
public:
  Egg() : AnimatedPicture(pics, &pics[0], 800, -1) {}
  void draw(Graphics* g) {
    g->drawPicture(*currentPicture, *this);
  }
};

const Picture Egg::pics[4] = {
  Picture(bmp_eggs_anim, 0, 0, 7, 7),
  Picture(bmp_eggs_anim, 7, 0, 7, 7),
  Picture(bmp_eggs_anim, 14, 0, 7, 7),
  Picture(bmp_eggs_anim, 21, 0, 7, 7),
};

//class EggRolling : public Sprite, public Animation {
//private:
//  Chicken chicken;
//  Egg egg;
//  FrameAnimation fa;
//  ValueAnimation<Position> animPos, animPos2;
//  ValueAnimation<bool> animShow;
//  Animation* anims[4] = {
//    &fa, &animShow, &animPos, &animPos2
//  };
//  SequenceAnimation sa;
//public:
//  Position pos;
//  EggRolling() :
//    fa(2, 300, 3),
//    animPos(egg.pos, { 10, 5 }, { 30, 15 }, 1500, 1),
//    animPos2(egg.pos, { 30, 15 }, { 30, 60 }, 1000, 1),
//    animShow(egg.show, false, true, 0, 1),
//    sa(anims, ::size(anims), 1) {
//    egg.show = false;
//    egg.pos = { 10, 5 };
//  }
//  void setPosition(Position pos)
//  {
//  }
//  void onStart(milliseconds now) override
//  {
//    sa.start(now);
//    egg.start(now);
//  }
//  void onStop() override
//  {
//    sa.stop();
//    chicken.frame = 0;
//    egg.show = false;
//    egg.stop();
//  }
//  void onUpdate(milliseconds now)
//  {
//    sa.update(now);
//    chicken.frame = fa.getCurrentFrame();
//    egg.update(now);
//  }
//  void onDraw(Graphics* g)
//  {
//    chicken.draw(g);
//    egg.draw(g);
//  }
//};

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

class Stage {
public:
  Background background;
  Wolf wolf;
  Egg egg;
};


void Core::init(Controller& c, Graphics& g)
{
  stage = new Stage;
  controller = &c;
  graphics = &g;

  stage->wolf.y = 8;
  stage->wolf.x = 38;

  stage->egg.y = 1;
  stage->egg.x = 1;

  c.init({ this, &Core::pressDown });

}

void Core::update()
{
  graphics->clear();

  stage->background.draw(graphics);
  stage->wolf.draw(graphics);
  stage->egg.update(millis());
  stage->egg.draw(graphics);

  controller->update();
}

void Core::pressDown(uint8_t button)
{
  switch (button) {
  case Controller::BUTTON_X:
    stage->wolf.x = 38;
    stage->wolf.basketLeftUp();
    stage->egg.start(millis());
    break;
  case Controller::BUTTON_Y:
    stage->wolf.x = 38;
    stage->wolf.basketLeftDown();
    break;
  case Controller::BUTTON_A:
    stage->wolf.x = 45;
    stage->wolf.basketRightDown();
    break;
  case Controller::BUTTON_B:
    stage->wolf.x = 45;
    stage->wolf.basketRightUp();
    break;
  }
}
