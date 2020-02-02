//Clickable.cpp
#include "Clickable.h"
#include "Application.h"

Clickable::Clickable()
{
  Application::events.onMouseUp.link(this, &Clickable::onMouseUp);
  Application::events.onMouseDown.link(this, &Clickable::onMouseDown);
  Application::events.onMouseMove.link(this, &Clickable::onMouseMove);
}

void Clickable::onMouseUp(Key key)
{
  if(rect.hasPoint(m_mousePosition))
  {
    switch(key)
    {
    case Key::MOUSE_L:
      if(m_clicked & 0b001)
      {
        m_clicked &= ~0b001;
        onClick();
      }
      break;
    case Key::MOUSE_R:
      if(m_clicked & 0b010)
      {
        m_clicked &= ~0b010;
        onClick();
      }
      break;
    case Key::MOUSE_M:
      if(m_clicked & 0b100)
      {
        m_clicked &= ~0b100;
        onClick();
      }
      break;
    }
  }
}

void Clickable::onMouseDown(Key key)
{
  if(rect.hasPoint(m_mousePosition))
  {
    switch(key)
    {
    case Key::MOUSE_L: m_clicked |= 0b001; break;
    case Key::MOUSE_R: m_clicked |= 0b010; break;
    case Key::MOUSE_M: m_clicked |= 0b100; break;
    }
  }
}

void Clickable::onMouseMove(Point16 position)
{
  m_mousePosition = position;
}
