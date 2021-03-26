#include "DButton.h"

void DButton::draw(Canvas & canvas)
{
  canvas.clear(background(), rect);
  canvas.drawText(rect, text(), color(), background(), ALIGN_TEXT_HCENTER | ALIGN_TEXT_VCENTER, true);
}
