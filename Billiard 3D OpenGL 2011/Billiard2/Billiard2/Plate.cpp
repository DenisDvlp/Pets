#include "Plate.h"
#include "Drawing.h"

void Plate::onDraw(GLUquadric* quadric) const
{
  materialReflection(1.0f, 1.0f);
  materialDiffusion(1.0f);
  glColor3f(1.0f, 0, 0);
  const float d = 0.2f;
  const float height = -2.1f;
  glNormal3f(0.0, 1.0, 0.0);
  glBegin(GL_QUADS);
  for (float x = -5.0; x < 5.0; x += d)
  {
    for (float y = 2.0; y > -10.0; y -= d)
    {
      glVertex3f(x, height, y);
      glVertex3f(x, height, y + d);
      glVertex3f(x + d, height, y + d);
      glVertex3f(x + d, height, y);
    }
  }
  glEnd();
}
