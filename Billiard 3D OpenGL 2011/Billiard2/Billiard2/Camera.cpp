#include "Camera.h"
#include "Utils.h"
#include <cmath>
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

void Camera::setBall(const Ball& ball)
{
  pos = -ball.position();
}

void Camera::moveForward()
{
  move(-1, 1, sin, cos);
}

void Camera::moveBackward()
{
  move(1, -1, sin, cos);
}

void Camera::moveLeft()
{
  move(1, 1, cos, sin);
}

void Camera::moveRight()
{
  move(-1, -1, cos, sin);
}

void Camera::rotate(float angleX, float angleY)
{
  adjustInRange<float>(-30, angleX, 90);
  adjustInLoop<float>(0, angleY, 360);
  angle.set(angleX, angleY);
}

Angle Camera::viewAngle() const
{
  return angle;
}

void Camera::draw() const
{
  glTranslatef(0, 1, -2.8f);
  glRotatef(angle.x(), 1, 0, 0);
  glRotatef(angle.y(), 0, 1, 0);
  glTranslatef(pos.x(), pos.y(), pos.z());
}

void Camera::move(int direction1, int direction2, float(*trig1)(float), float(*trig2)(float))
{
  const float radian = degToRad(angle.y());
  pos.x() += direction1 * speed * trig1(radian);
  pos.z() += direction2 * speed * trig2(radian);
  adjustInRange<float>(-5, pos.x(), 5);
  adjustInRange<float>(-10.0f, pos.z(), 10.0f);
}
