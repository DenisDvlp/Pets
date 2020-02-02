// Figure.cpp
#include "Figure.h"

void Figure::onDraw(IDraw* draw)
{
    draw->drawRect(m_rect, color);

    draw->drawText(m_rect, "Hello world!", Color::WHITE, Align::CENTER_CENTER);
}