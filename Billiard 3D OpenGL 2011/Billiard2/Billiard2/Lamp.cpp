#include "Lamp.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Lamp::onInit()
{
  light.position(0, 0, 0);
  light.direction(0, -1.0f, 0);
  light.ambient(0.0f, 0.0f, 0.0f);
  light.diffusion(0.05f, 0.05f, 0.05f);
  light.specular(1.0f, 1.0f, 1.0f);
  light.cutoffAngle(45.0f);
}

void Lamp::onDraw(GLUquadric* quadric) const
{
  light.draw(quadric);
  
  glRotatef(-90, 1, 0, 0);

  glPushAttrib(GL_LIGHTING_BIT);
  glColor3f(0.3f, 0.7f, 0.5f);
  GLfloat spec[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
  gluCylinder(quadric, 0.7f, 0.2f, 0.6f, 64, 32);
  glPopAttrib();

  glPushAttrib(GL_LIGHTING_BIT);
  GLfloat emm[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  glMaterialfv(GL_FRONT, GL_EMISSION, emm);
  gluCylinder(quadric, 0.69f, 0.19f, 0.59f, 32, 1);
  glPopAttrib();

  glTranslatef(0, 0, 0.6f);
  gluDisk(quadric, 0.1f, 0.2f, 64, 32);

}
