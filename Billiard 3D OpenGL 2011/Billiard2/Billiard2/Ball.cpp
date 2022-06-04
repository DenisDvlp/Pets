#include "Ball.h"
#include "Utils.h"
#include "Drawing.h"
#include <cmath>

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
  // ball
  glColor4fv(rgb);
  {
    materialBlock;
    materialReflection(1.0f, 1.0f);
    materialDiffusion(1.0f);
    gluSphere(quadric, 0.068f, 48, 48);
  }

  // shadow
  glColor3f(0.3f, 0.6f, 0.3f);
  glTranslatef(0, -0.0678f, 0);
  glRotatef(-90, 1, 0, 0);
  gluDisk(quadric, 0.0f, 0.055f, 16, 16);
}
