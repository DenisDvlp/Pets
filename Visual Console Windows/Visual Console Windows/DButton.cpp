#include "DButton.h"

DButton::DButton()
{
    subscribeSystemMessages({MessageType::MOUSE_MOVE});
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

void DButton::onSystemMouseMove(const DPoint& point)
{
    if(m_status != StatusType::Click)
    {
        m_status = rect().contains(point) ? StatusType::Hover : StatusType::Main;
    }
}
