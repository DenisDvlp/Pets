#include "Primitive.h"

void Primitive::onDraw(IDraw* draw)
{
    draw->drawRect(m_rect, color);
    draw->drawText(m_rect, text, textColor, textAlign);
}
