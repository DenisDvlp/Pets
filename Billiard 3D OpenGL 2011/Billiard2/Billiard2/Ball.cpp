#include "Ball.h"
#include "Utils.h"
#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Ball::color(GLubyte r, GLubyte g, GLubyte b)
{
  rgb[0] = r;
  rgb[1] = g;
  rgb[2] = b;
}

void Ball::collide(Ball& other)
{
}

void Ball::pull(float acceleration, float angle)
{
  this->acceleration = acceleration;
  this->angle = angle;
}

void Ball::update()
{
  if (!visible)
    return;

  const float radian = degToRad(angle);
  auto decelerate = [&](float&x, float(*trig)(float))
  {
    x -= speed * trig(radian) * acceleration;
  };

  decelerate(pos.x, sin);
  decelerate(pos.y, cos);
}

const Position& Ball::position() const
{
  return pos;
}

bool Ball::isVisible() const
{
  return visible;
}

void Ball::position(float x, float z)
{
  pos = { x, pos.y, z };
}

void Ball::position(float x, float y, float z)
{
  pos = { x, y, z };
}

bool Ball::isMoving() const
{
  return acceleration > 0;
}

void Ball::draw()
{
  if (!visible)
    return;

  glPushMatrix();
  // ball
  glColor3ubv(rgb);
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 128 };
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  glTranslatef(pos.x, pos.y, pos.z);
  gluSphere(*quadric, 0.068f, 48, 48);

  // shadow
  GLfloat mat_specular2[] = { 0.0, 0.0, 0.0, 1.0 };
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
  glTranslatef(0, -0.0678f, 0);
  glRotatef(-90, 1, 0, 0);
  glColor3f(0.3f, 0.6f, 0.3f);
  gluDisk(*quadric, 0.0f, 0.055f, 16, 16);

  glPopMatrix();
}
