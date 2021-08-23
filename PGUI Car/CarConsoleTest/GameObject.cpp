#include "GameObject.h"

GameObject::GameObject()
{
  road_ = new Rect[Application::instance().height];
  for (int i = 0; i < Application::instance().height; i++)
  {
    road_[i].set(
      Application::instance().width * 0.25, i,
      Application::instance().width * 0.5,  1
    );
  }
  car_ = Rect(Application::instance().width * 0.5f, Application::instance().height - 6, 4, 5);
  barriers_[0] = Rect(random(road_[0].x, road_[0].getRight()),
    random(-Application::instance().height * 0.7f, -3), 4, 2);
  barriers_[1] = Rect(random(road_[0].x, road_[0].getRight()),
    random(-Application::instance().height * 0.7f, -3), 4, 2);
  barriers_[2] = Rect(random(road_[0].x, road_[0].getRight()),
    random(-Application::instance().height * 0.7f, -3), 6, 3);
  for (int i = 0; i < barrierCount; i++)
  {
    barrierColors[i] = random(COLOR_BLUE, COLOR_YELLOW);
  }
}

GameObject::~GameObject()
{
  delete[] road_;
}

void GameObject::onUpdate()
{
  //keys

  if (toLeft)
  {
    car_.x -= 2;
  }
  if (toRight)
  {
    car_.x += 2;
  }

  if (speedUp)
  {
    speed_ += 0.1f;
  }
  if (speedDown)
  {
    speed_ -= 0.15f;
  }
  speed_ -= 0.01f;
  speed_ = range(0.1f, speed_, 5.0f);

  //update

  float prev = pos_;
  pos_ += speed_;

  int deltaY = int(pos_) - int(prev);

  for (int repeat = 0; repeat < deltaY; repeat++)
  {
    roaddirectioniterator_--;
    if (roaddirectioniterator_ < 0)
    {
      roaddirectioniterator_ = random(10, 100);
      roaddirection_ = roaddirection_ == 1 ? 0 : 1;
    }
    for (int i = Application::instance().height - 1; i > 0; i--)
    {
      road_[i].set(road_[i - 1].x, i, road_[i - 1].getWidth(), 1);
    }
    int x = road_[0].x + random(roaddirection_ ? -1 : 0, roaddirection_ ? 0 : 1);
    road_[0].x = range(Application::instance().width * 0.05, x, Application::instance().width * 0.45);
  }
  for (int i = 0; i < barrierCount; i++)
  {
    int y = barriers_[i].y + deltaY;
    if (y >= Application::instance().height)
    {
      barrierColors[i] = random(COLOR_BLUE, COLOR_YELLOW);
      y = random(-20, -3);
      int x = road_[0].getWidth() / 2 + road_[0].x + random(-road_[0].getWidth() * 0.4, road_[0].getWidth() * 0.3);
      barriers_[i].x = x;
    }
    barriers_[i].y = y;
  }
  score_ += deltaY;

  pos_ = pos_ - int(pos_);

  //collision

  for (int i = 0; i < Application::instance().height; i++)
  {
    if ( car_.isIntersectRect(Rect(-1000, i, road_[i].x + 1000, 1)) )
    {
      car_.x++;
    }
    if (car_.isIntersectRect(Rect(road_[i].getRight(), i, 1000, 1)) )
    {
      car_.x--;
    }
  }
  for (int i = 0; i < barrierCount; i++)
  {
    if (car_.isIntersectRect(barriers_[i]))
    {
      //Application::instance().close();
    }
  }
}

void GameObject::onKeyDown(int key)
{
  switch (key)
  {
  case KEY_ARROW_UP:    speedUp   = true; break;
  case KEY_ARROW_DOWN:  speedDown = true; break;
  case KEY_ARROW_LEFT:  toLeft    = true; break;
  case KEY_ARROW_RIGHT: toRight   = true; break;
  default:                                break;
  }
}

void GameObject::onKeyUp(int key)
{
  switch (key)
  {
  case KEY_ARROW_UP:    speedUp    = false; break;
  case KEY_ARROW_DOWN:  speedDown  = false; break;
  case KEY_ARROW_LEFT:  toLeft     = false; break;
  case KEY_ARROW_RIGHT: toRight    = false; break;
  default:                                  break;
  }
}

void GameObject::onDraw(Canvas & canvas)
{
  //field
  canvas.clear(COLOR_DARKGREEN);
  //road
  for (int i = 0; i < Application::instance().height; i++)
  {
    canvas.clear(COLOR_GRAY, road_[i]);
    canvas.drawCell(road_[i].x, road_[i].y, ' ', COLOR_GRAY, COLOR_WHITE);
    canvas.drawCell(road_[i].getRight() - 1, road_[i].y, ' ', COLOR_GRAY, COLOR_WHITE);
  }
  //barrier
  for (int i = 0; i < barrierCount; i++)
  {
    canvas.clear(barrierColors[i], barriers_[i]);
  }
  //car
  canvas.clear(COLOR_RED - 8, car_);
  canvas.clear(COLOR_RED, Rect(car_.x, car_.y + 2, 4, 2));
  canvas.drawRect(Rect(car_.x + 1, car_.y, 2, 2), '|', COLOR_WHITE, COLOR_TRANSPARENT);
  canvas.drawCell(car_.x - 1,      car_.y + 1, ' ', COLOR_BLACK, COLOR_BLACK);
  canvas.drawCell(car_.getRight(), car_.y + 1, ' ', COLOR_BLACK, COLOR_BLACK);
  canvas.drawCell(car_.x - 1,      car_.y + 4, ' ', COLOR_BLACK, COLOR_BLACK);
  canvas.drawCell(car_.getRight(), car_.y + 4, ' ', COLOR_BLACK, COLOR_BLACK);
  //text
  canvas.drawText(1, 1, "SCORE:" + std::to_string(score_), COLOR_YELLOW, COLOR_BLACK);
  canvas.drawText(1, 3, "SPEED:" + std::to_string(int(speed_ * 10)), COLOR_YELLOW, COLOR_BLACK);
  if (!isEnabled)
  {
    canvas.drawText(1, 5, "PAUSED", COLOR_YELLOW, COLOR_BLACK);
  }
}
