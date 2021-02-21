#include "DButton.h"

DButton::DButton(Key key) : m_key(key)
{
}

void DButton::setMainColor(DColor color)
{
  m_colors[StatusType::Main] = color;
}

void DButton::setClickColor(DColor color)
{
  m_colors[StatusType::Click] = color;
}

void DButton::setDisableColor(DColor color)
{
  m_colors[StatusType::Disable] = color;
}

void DButton::setHoverColor(DColor color)
{
  m_colors[StatusType::Hover] = color;
}

void DButton::draw(IDDraw& draw) const
{
    draw.drawRect(rect(), m_colors[m_status]);
}

void DButton::onSystemMouseMove(const DMouseMessage& msg)
{
    if(m_status != StatusType::Click)
    {
        m_status = rect().contains(msg.position) ? StatusType::Hover : StatusType::Main;
    }
}

void DButton::onSystemMouseUp(const DMouseMessage& msg)
{
    if(m_status == StatusType::Click)
    {
        m_status = StatusType::Main;
    }
}

void DButton::onSystemMouseDown(const DMouseMessage& msg)
{
    m_status = StatusType::Click;
}

void DButton::onSystemKeyUp(Key key)
{
  if(key == m_key)
  {
    m_status = StatusType::Main;
  }
}

void DButton::onSystemKeyDown(Key key)
{
  if (key == m_key)
  {
    m_status = StatusType::Click;
  }
}
