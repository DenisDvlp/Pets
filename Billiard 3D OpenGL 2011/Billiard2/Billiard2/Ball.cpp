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

void Ball::pull(float velocity, float angle)
{
  this->velocity = velocity;
  this->angle = angle;
}

void Ball::collide(float angle)
{
  this->angle = angle * 2 - this->angle;
}

void Ball::update(milliseconds ms)
{
  if (!visible() || velocity <= 0)
    return;

  auto decelerate = [angle = this->angle](float&x, float path, float(*trig)(float))
  {
    x -= path * trig(angle);
  };

  const float partOfSecond = ms.count() / 1000.0f;
  const float path = partOfSecond * (velocity + deceleration * partOfSecond / 2);
  velocity = velocity + deceleration * partOfSecond;

  decelerate(pos.x(), path, Sin);
  decelerate(pos.z(), path, Cos);
}

void Ball::position(float x, float z)
{
  position(x, -1.932f, z);
}

bool Ball::isMoving() const
{
  return velocity > 0;
}

void Ball::onDraw(GLUquadric* quadric) const
{
  // ball
  glColor4fv(rgb);

  {
    materialBlock;
    materialReflection(1.0f, 1.0f);
    materialDiffusion(1.0f);
    materialAmbient(0.0f);
    gluSphere(quadric, 0.068f, 64, 64);
  }

  // shadow
  glColor3i(0, 91, 63);
  ::position(0, -0.0678f, 0);
  glRotatef(-90, 1, 0, 0);
  gluDisk(quadric, 0.0f, 0.055f, 16, 16);
}
