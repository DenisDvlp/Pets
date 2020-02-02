//MouseInteractable.cpp
#include "MouseInteractable.h"
#include "Application.h"

MouseInteractable::MouseInteractable()
{
  Application::events.onMouseUp.link(this, &MouseInteractable::linkOnMouseUp);
  Application::events.onMouseDown.link(this, &MouseInteractable::linkOnMouseDown);
  Application::events.onMouseMove.link(this, &MouseInteractable::linkOnMouseMove);
}

void MouseInteractable::linkOnMouseUp(Key key)
{
  if(rect.hasPoint(m_mousePosition))
  {
    onMouseUp(key);
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

void MouseInteractable::linkOnMouseDown(Key key)
{
  if(rect.hasPoint(m_mousePosition))
  {
    onMouseDown(key);
    switch(key)
    {
    case Key::MOUSE_L: m_clicked |= 0b001; break;
    case Key::MOUSE_R: m_clicked |= 0b010; break;
    case Key::MOUSE_M: m_clicked |= 0b100; break;
    }
  }
}

void MouseInteractable::linkOnMouseMove(Point16 position)
{
  m_mousePosition = position;
  onMouseMove(m_mousePosition);
  if(rect.hasPoint(m_mousePosition))
  {
    if(!m_isEntered)
    {
      m_isEntered = true;
      onMouseEnter();
    }
  }
  else if(m_isEntered)
  {
    m_isEntered = false;
    onMouseLeave();
  }
}