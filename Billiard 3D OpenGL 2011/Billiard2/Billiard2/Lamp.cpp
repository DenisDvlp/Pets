#include "Lamp.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

unsigned int Lamp::lastLightId = GL_LIGHT0 + 1;

Lamp::Lamp() : lightId(lastLightId++)
{
  glEnable(lightId);
}
void Lamp::position(float x, float y, float z)
{
  pos = { x, y, z };
}

void Lamp::draw()
{
  glPushMatrix();

  glPushAttrib(GL_LIGHTING_BIT);

  glRotatef(90, 1, 0, 0);
  glTranslatef(pos.x, pos.y, pos.z);

  glColor3f(0.3f, 0.7f, 0.5f);
  GLfloat spec[] = { 1, 1, 1, 1 };
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, spec);
  gluCylinder(*quadric, 0.2f, 0.7f, 0.6f, 64, 32);

  GLfloat emm[] = { 1, 1, 1, 1 };
  glMaterialfv(GL_FRONT, GL_EMISSION, emm);
  gluCylinder(*quadric, 0.19f, 0.69f, 0.6f, 32, 1);
  glPopAttrib();

  gluSphere(*quadric, 0.068f, 48, 48);

  GLfloat spotLight[] = { 0, 0, 0, 1 };
  glLightfv(lightId, GL_POSITION, spotLight);
  GLfloat diffuse[] = { 0.1, 0.1, 0.1, 1.0 };
  glLightfv(lightId, GL_DIFFUSE, diffuse);
  GLfloat spec2[] = { 1, 1, 1, 0 };
  glLightfv(lightId, GL_SPECULAR, spec2);
  GLfloat light_spot_direction[] = { 0.0, 0.0, 1.0 };
  glLightfv(lightId, GL_SPOT_DIRECTION, light_spot_direction);
  glLightf(lightId, GL_SPOT_CUTOFF, 45);

  glPopMatrix();
}
