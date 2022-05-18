#include "Lamp.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

unsigned int Lamp::lastLightId = GL_LIGHT0 + 1;

void Lamp::position(float x, float y, float z)
{
  pos = { x, y, z };
}

void Lamp::draw()
{
  glPushMatrix();

  glRotatef(90, 1, 0, 0);
  glTranslatef(pos.x, pos.y, pos.z);

  glColor3f(0.3f, 0.7f, 0.5f);
  gluCylinder(*quadric, 0.2f, 0.7f, 0.6f, 32, 1);

  glColor3f(1.0f, 1.0f, 1.0f);
  gluCylinder(*quadric, 0.19f, 0.69f, 0.6f, 32, 1);

  glEnable(lightId);

  glPushMatrix();
  GLfloat spotLight[] = { 0, 0, 0, 1 };
  glLightfv(lightId, GL_POSITION, spotLight);
  GLfloat diffuse[] = { 0, 0, 0, 0 };
  glLightfv(lightId, GL_DIFFUSE, diffuse);
  GLfloat spec2[] = { 1, 1, 1, 0 };
  glLightfv(lightId, GL_SPECULAR, spec2);

  glPopMatrix();

  //GLfloat light_position[] = { 0.0, 0.0, 0.0, 1.0 };
  //GLfloat light_spot_direction[] = { 0.0, 0.0, 1.0 };
  //GLfloat ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  //GLfloat diffuse[] = { 0.0f, 0.0f, 0.0f, 1.0f };
  //GLfloat specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
  //glLightfv(lightId, GL_AMBIENT, ambient);
  //glLightfv(lightId, GL_DIFFUSE, diffuse);
  //glLightfv(lightId, GL_SPECULAR, specular);
  //glLightfv(lightId, GL_POSITION, light_position);
  //glLightfv(lightId, GL_SPOT_DIRECTION, light_spot_direction);
  //glLightf(lightId, GL_SPOT_CUTOFF, 45);
}
