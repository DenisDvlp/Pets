#include "Plate.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Plate::onDraw(GLUquadric* quadric) const
{
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 128 };
  Color rgb = {1.0f, 0, 0, 0};
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glColor3fv(rgb);
  GLfloat x, y;
  glBegin(GL_QUADS);
  const float d = 0.2f;
  const float height = -2.1f;
  glNormal3f(0.0, 1.0, 0.0);
  for (x = -5.0; x < 5.0; x += d)
  {
    for (y = 2.0; y > -10.0; y -= d)
    {
      glVertex3f(x, height, y);
      glVertex3f(x, height, y + d);
      glVertex3f(x + d, height, y + d);
      glVertex3f(x + d, height, y);
    }
  }
  glEnd();
}
