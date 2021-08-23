#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include "Object.h"
#include "Application.h"

class MenuObject :
  public Object
{
public:
  enum Message
  {
    MESSAGE_NONE,
    MESSAGE_PLAY,
    MESSAGE_EXIT,
  };
private:
  Rect mainRect_;
  Rect items_[2];
  int choosenIndex_ = 0;
  Message message_ = MESSAGE_NONE;
public:
  MenuObject();
  virtual void onKeyDown(int key);
  virtual void onDraw(Canvas &canvas);
  Message getMessage();
  void clearMessage();
};

#endif // MENUOBJECT_H