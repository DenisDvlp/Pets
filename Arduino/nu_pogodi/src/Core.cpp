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

class RollingEggAnimation: public Position {
  static const Picture pic_egg[4];
  const Path<Position> path_egg[3] = {
    {{11,6}, 0},
    {{31,16}, 1000},
    {{31,64}, 700},
  };

  int index = -1;
  int flip = false;
  Animation<int> rotatingAnimation{index, 0, 3, 500};
public:
  RollingEggAnimation(bool flip) : flip(flip) {

  }

  void startRolling(milliseconds now) {
    rotatingAnimation.start(now);
  }

  void draw(Graphics* g) {
    if (index >= 0)
      g->drawPicture(pic_egg[index], *this, flip);
  }
};

const Picture RollingEggAnimation::pics[4] = {
  Picture(bmp_eggs_anim, 0, 0, 7, 7),
  Picture(bmp_eggs_anim, 7, 0, 7, 7),
  Picture(bmp_eggs_anim, 14, 0, 7, 7),
  Picture(bmp_eggs_anim, 21, 0, 7, 7),
};

class Egg: public Position, public Animation<int> {
  static const Picture pics[4];
  int index = -1;
public:
  Egg() : Animation(index, 0, 3, 500) {}
  void draw(Graphics* g) {
    if (index >= 0)
      g->drawPicture(pics[index], *this);
  }
};

const Picture Egg::pics[4] = {
  Picture(bmp_eggs_anim, 0, 0, 7, 7),
  Picture(bmp_eggs_anim, 7, 0, 7, 7),
  Picture(bmp_eggs_anim, 14, 0, 7, 7),
  Picture(bmp_eggs_anim, 21, 0, 7, 7),
};

class Chick: public Position, public Animation<int> {
  static const Picture pics[6];
  int index = 0;
public:
  bool flip = false;
  Chick() : Animation(index, 0, 5, 400, 1) {}
  void draw(Graphics* g) {
    g->drawPicture(pics[index], *this, flip);
  }
};

const Picture Chick::pics[] = {
  Picture(bmp_chick_anim, 0, 0, 11, 12),
  Picture(bmp_chick_anim, 11, 0, 11, 12),
  Picture(bmp_chick_anim, 22, 0, 11, 12),
  Picture(bmp_chick_anim, 11, 0, 11, 12),
  Picture(bmp_chick_anim, 22, 0, 11, 12),
  Picture(bmp_chick_anim, 0, 0, 11, 12),
};

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
  static const Path<Position> eggPath[3];
public:
  Background background;
  Wolf wolf;
  Egg egg;
  Chick chick[4];
  Animation<Position> eggPosAnim{egg, eggPath};

  void init() {
    wolf.x = 38;
    wolf.y = 8;

    egg.x = 10;
    egg.y = 5;

    chick[0].x = 1;
    chick[0].y = 0;

    chick[1].x = 1;
    chick[1].y = 19;

    chick[2].flip = true;
    chick[2].x = 116;
    chick[2].y = 0;

    chick[3].flip = true;
    chick[3].x = 116;
    chick[3].y = 19;
  }

  void init(milliseconds now, Graphics* g) {
    background.draw(g);

    eggPosAnim.update(now);
    egg.update(now);
    egg.draw(g);

    wolf.draw(g);

    for (int i = 0; i < 4; i++) {
      chick[i].update(now);
      chick[i].draw(g);
    }
  }
};

const Path<Position> Stage::eggPath[] {
  {{11,6}, 0},
  {{31,16}, 1000},
  {{31,64}, 700},
};


void Core::init(Controller& c, Graphics& g)
{
  controller = &c;
  graphics = &g;

  c.init({ this, &Core::pressDown });

  stage = new Stage;
  stage->init();
}

void Core::update()
{
  graphics->clear();
  controller->update();
  stage->init(millis(), graphics);
}

void Core::pressDown(uint8_t button)
{
  const auto now = millis();
  switch (button) {
  case Controller::BUTTON_X:
    stage->wolf.x = 38;
    stage->wolf.basketLeftUp();
    stage->eggPosAnim.stop();
    stage->eggPosAnim.start(now);
    stage->egg.start(now);
    break;
  case Controller::BUTTON_Y:
    stage->wolf.x = 37;
    stage->wolf.basketLeftDown();
    for (int i = 0; i < 4; i++) {
      stage->chick[i].start(now);
    }
    break;
  case Controller::BUTTON_A:
    stage->wolf.x = 46;
    stage->wolf.basketRightDown();
    break;
  case Controller::BUTTON_B:
    stage->wolf.x = 45;
    stage->wolf.basketRightUp();
    break;
  }
}
