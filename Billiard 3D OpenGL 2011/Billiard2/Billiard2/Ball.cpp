#include "Ball.h"
#include "Utils.h"
#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Ball::color(float r, float g, float b)
{
  rgb.set(r, g, b);
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
  if (!visible())
    return;

  const float radian = degToRad(angle);
  auto decelerate = [&](float&x, float(*trig)(float))
  {
    x -= speed * trig(radian) * acceleration;
  };

  decelerate(pos.x(), Sin);
  decelerate(pos.y(), Cos);
}

void Ball::position(float x, float z)
{
  position(x, -1.932f, z);
}

bool Ball::isMoving() const
{
  return acceleration > 0;
}

void Ball::onDraw(GLUquadric* quadric) const
{
  glPushAttrib(GL_LIGHTING_BIT);
  // ball
  glColor4fv(rgb);
  GLfloat diffuse[] = { 0.0, 0.0, 1.0, 0.0 };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 128 };
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

  gluSphere(quadric, 0.068f, 48, 48);

  // shadow
  GLfloat mat_specular2[] = { 0.0, 0.0, 0.0, 1.0 };
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular2);
  glTranslatef(0, -0.0678f, 0);
  glRotatef(-90, 1, 0, 0);
  glColor3f(0.3f, 0.6f, 0.3f);
  gluDisk(quadric, 0.0f, 0.055f, 16, 16);
  glPopAttrib();
}
