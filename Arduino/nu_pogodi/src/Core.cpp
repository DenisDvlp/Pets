#include "Core.hpp"
#include "FontCirillic.hpp"
#include "Images.hpp"
#include "Sprite.hpp"
#include "Animation.hpp"
#include "stl.hpp"

static constexpr char scoreText[] = u8"счёт:";
static constexpr char captionText[] = u8"НУ ПОГОДИ";
static constexpr char captionHelpText[] = u8"(нажми любую кнопку)";

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
  bool checkCatch(Position eggPos) {
    const bool isUp = (currentBasket.x == 0);
    Position basketPos = { x + (basketRight ? 46 : -3), y + (isUp ? 13 : 30) };
    constexpr int distance = 4;
    const int dx = eggPos.x - basketPos.x;
    const int dy = eggPos.y - basketPos.y;
    const bool caught = (dx * dx + dy * dy <= distance * distance);
    if (caught) {
      return true;
    }
    return (dx * dx + dy * dy <= distance * distance);
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

class RollingEgg: public Position {
  static const Picture pic_egg[4];
  Path<Position> path_egg[3];

  int index = 0;
  Animation<int> rotatingAnimation{ index, 0, 3, 400, 3, 400 };
  Animation<Position> rollingAnimation{ *this, path_egg, 1 };
public:
  int flip = false;

  RollingEgg(Function<void()> onFinish) {
    rollingAnimation.onFinish = onFinish;
  }

  void startRolling(milliseconds now) {
    path_egg[0] = { *this, 400 };
    path_egg[1] = { *this + Position{20 * (-flip + !flip),11}, 1200 };
    path_egg[2] = { *this + Position{20 * (-flip + !flip), 64}, 500 };
    index = 0;
    rotatingAnimation.start(now);
    rollingAnimation.start(now);
  }

  void stopRolling() {
    rotatingAnimation.stop();
    rollingAnimation.stop();
  }

  void update(milliseconds now) {
    rotatingAnimation.update(now);
    rollingAnimation.update(now);
  }

  void draw(Graphics* g) {
    if (index >= 0)
      g->drawPicture(pic_egg[index], *this, flip);
  }
};

const Picture RollingEgg::pic_egg[4] = {
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

class EggSpawner {
  milliseconds spawnsAfterMs[4]{};
public:
  Function<void(int, milliseconds)> onEggSpawn;

  void start(milliseconds now) {
    for (size_t i = 0; i < 4; i++) {
      spawnsAfterMs[i] = now + random(2000, 5000);
    }
  }

  void update(milliseconds now) {
    for (size_t i = 0; i < 4; i++) {
      if (now >= spawnsAfterMs[i]) {
        onEggSpawn(i, now);
        spawnsAfterMs[i] = now + random(2000, 5000);
      }
    }
  }
};

static FontCirillic font;
//
//class ScoreTable {
//  static const Picture pics[2];
//  int positiveScore = 0;
//  int negativeScore = 0;
//public:
//  ScoreTable() {}
//
//  void operator++() {
//    ++positiveScore;
//  }
//
//  void operator--() {
//    ++negativeScore;
//  }
//
//  void draw(Graphics* g) {
//    font.isBold = false;
//    font.size = 0;
//
//    g->fillRect({ 102, 54 }, { 27, 10 }, false);
//    g->fillRect({ 103, 55 }, { 25, 8 }, true);
//
//    g->drawPicture(pics[0], {104, 56});
//    char scoreStr[] = {
//      static_cast<char>(positiveScore / 100 % 10 + 48),
//      static_cast<char>(positiveScore / 10 % 10 + 48),
//      static_cast<char>(positiveScore % 10 + 48),
//      0
//    };
//    g->drawText(scoreStr, { 112, 55 }, font);
//
//    g->fillRect({ -1, 54 }, { 26, 9 }, false);
//    g->fillRect({ 0, 55 }, { 25, 8 }, true);
//
//    g->drawPicture(pics[1], { 1, 56 });
//    scoreStr[0] = static_cast<char>(negativeScore / 100 % 10 + 48);
//    scoreStr[1] = static_cast<char>(negativeScore / 10 % 10 + 48);
//    scoreStr[2] = static_cast<char>(negativeScore % 10 + 48);
//    g->drawText(scoreStr, { 9, 55 }, font);
//  }
//};
//
//const Picture ScoreTable::pics[2] = {
//  Picture(bmp_eggs_anim, 0, 0, 7, 7),
//  Picture(bmp_eggs_anim, 28, 0, 7, 7),
//};

constexpr auto stageTypeUnknown = 0;
constexpr auto stageTypeStart = 1;
constexpr auto stageTypeGame = 2;

class Stage {
public:
  static constexpr int stageType = stageTypeUnknown;
  const int type = stageTypeUnknown;
  Stage(int type) : type(type) {}
  virtual ~Stage() = default;
  virtual void init() = 0;
  virtual void update(milliseconds, Graphics*) = 0;
  template<typename T>
  T* castAs() {
    if (T::stageType != type)
      return nullptr;
    return (T*)(this);
  };
};

class GameStage: public Stage {
  static const Path<Position> eggPath[3];
public:
  static constexpr int stageType = stageTypeGame;
  Background background;
  Wolf wolf;
  RollingEgg egg[4];
  Chick chick[4];
  EggSpawner eggSpawner;
  //ScoreTable score;

  GameStage() : Stage(stageTypeGame), egg{
  Function<void()>{[this]() {onAnimationFinish(); }},
  Function<void()>{[this]() {onAnimationFinish(); }},
  Function<void()>{[this]() {onAnimationFinish(); }},
  Function<void()>{[this]() {onAnimationFinish(); }},
  } {}

  void onAnimationFinish() {
    //--score;
  }

  void init() {
    wolf.x = 38;
    wolf.y = 8;

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

    for( int i = 0; i < 4; i++) {
      egg[i].x = -10;
      egg[i].y = -10;
    }
    egg[2].flip = true;
    egg[3].flip = true;

    eggSpawner.onEggSpawn = [this](int i, milliseconds now) {
      Position pos{};
      switch (i) {
        case 0:
          pos.x = 11;
          pos.y = 6;
          break;
        case 1:
          pos.x = 11;
          pos.y = 25;
          break;
        case 2:
          pos.x = 110;
          pos.y = 6;
          break;
        case 3:
          pos.x = 110;
          pos.y = 25;
          break;
      }
      chick[i].start(now);
      egg[i].x = pos.x;
      egg[i].y = pos.y;
      egg[i].startRolling(now);
    };
    eggSpawner.start(millis());
  }

  void update(milliseconds now, Graphics* g) {
    // add objects
    eggSpawner.update(now);

    // change positions
    for (int i = 0; i < 4; i++) {
      chick[i].update(now);
      egg[i].update(now);
    }

    // check collisions
    for (int i = 0; i < 4; i++) {
      if (wolf.checkCatch(egg[i] + Position{3, 3})) {
        egg[i].stopRolling();
        egg[i].x = -10;
        egg[i].y = -10;
        //++score;
      }
    }

    // draw results
    background.draw(g);
    wolf.draw(g);
    for (int i = 0; i < 4; i++) {
      chick[i].draw(g);
      egg[i].draw(g);
    }

    // draw score
    //score.draw(g);
  }
};

class StartStage: public Stage {
public:
  static constexpr int stageType = stageTypeStart;
  StartStage() : Stage(stageType) {}
  void init() {}
  void update(milliseconds now, Graphics* g) {
    const auto bufSize = g->size();
    g->fillRect({ 2, 2 }, bufSize - 4, false);
    g->fillRect({ 5, 5 }, bufSize - 10, true);
    font.isBold = true;
    font.size = 4;
    g->drawText(captionText, { 22, 20 }, font);
    font.isBold = false;
    font.size = 0;
    g->drawText(captionHelpText, { 18, 40 }, font);
  }
};

void Core::init(Controller& c, Graphics& g)
{
  controller = &c;
  graphics = &g;

  c.init({ this, &Core::pressDown });

  stage = new StartStage;
}

void Core::update()
{
  // Clean screen
  graphics->clear();
  // Check inputs from keyboard/controller
  controller->update();
  // Update stage
  stage->update(millis(), graphics);
}

void Core::pressDown(uint8_t button)
{
  auto startStage = stage->castAs<StartStage>();
  if (startStage) {
    delete stage;
    stage = new GameStage;
    stage->init();
    return;
  }
  auto gameStage = stage->castAs<GameStage>();
  switch (button) {
  case Controller::BUTTON_X:
    gameStage->wolf.x = 38;
    gameStage->wolf.basketLeftUp();
    break;
  case Controller::BUTTON_Y:
    gameStage->wolf.x = 37;
    gameStage->wolf.basketLeftDown();
    break;
  case Controller::BUTTON_A:
    gameStage->wolf.x = 46;
    gameStage->wolf.basketRightDown();
    break;
  case Controller::BUTTON_B:
    gameStage->wolf.x = 45;
    gameStage->wolf.basketRightUp();
    break;
  }
}
