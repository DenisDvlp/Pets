#include "Application.h"
#include "Macros.h"
#include <ctime>
#include <algorithm>

Application::Application() :
  console_(80, 60),
  canvas_(console_.getWidth(), console_.getHeight()),
  width(console_.getWidth()),
  height(console_.getHeight())
{}

Application& Application::instance()
{
  static Application inst;
  return inst;
}

void Application::close()
{
  opened_ = false;
}

void Application::addObject(Object * object)
{
  if (object != nullptr)
  {
    objects_.push_back(object);
  }
}

void Application::removeObject(Object * object)
{
  if (object != nullptr)
  {
    objects_.erase(std::remove(objects_.begin(), objects_.end(), object), objects_.end());
  }
}

void Application::run()
{
  update();
  while (opened_)
  {
    DWORD millis = clock();
    checkKeyboard();
    update();
    millis = clock() - millis;
    if (millis < delay)
    {
      Sleep(delay - millis);
    }
  }
}

void Application::checkKeyboard()
{
  bool state = false;
  for (int i = 1; i < 256; i++)
  {
    state = HIWORD(GetKeyState(i));
    if (state)
    {
      if (!keyStates_[i])
      {
        for (Object* object : objects_)
        {
          if (object->isEnabled)
          {
            object->onKeyDown(i);
          }
        }
      }
    }
    else if (keyStates_[i])
    {
      for (Object* object : objects_)
      {
        if (object->isEnabled)
        {
          object->onKeyUp(i);
        }
      }
    }
    keyStates_[i] = state;
  }
}

void Application::update()
{
  canvas_.clear(COLOR_BLACK);
  for (Object* object : objects_)
  {
    if (object->isEnabled)
    {
      object->onUpdate();
    }
    if (object->isVisible)
    {
      object->onDraw(canvas_);
    }
  }
  canvas_.display(console_);
}