#ifndef MAINOBJECT_H
#define MAINOBJECT_H

#include "Object.h"
#include "Application.h"
#include "MenuObject.h"
#include "GameObject.h"

class MainObject :
  public Object
{
  MenuObject menu_;
  GameObject game_;
public:
  MainObject();
  virtual void onKeyDown(int key);
  virtual void onUpdate();
};

#endif // MAINOBJECT_H