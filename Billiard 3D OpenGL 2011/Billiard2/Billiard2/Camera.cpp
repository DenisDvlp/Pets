#include "Camera.h"
#include "Utils.h"
#include <cmath>
#include "Drawing.h"

void Camera::setBall(const Ball& ball)
{
  pos = -ball.position();
}

void Camera::moveForward()
{
  move(-1, 1, Sin, Cos);
}

void Camera::moveBackward()
{
  move(1, -1, Sin, Cos);
}

void Camera::moveLeft()
{
  move(1, 1, Cos, Sin);
}

void Camera::moveRight()
{
  move(-1, -1, Cos, Sin);
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
  ::position(0, 1, -2.8f);
  rotationX(angle.x());
  rotationY(angle.y());
  ::position(pos);
}

void Camera::move(int direction1, int direction2, float(*trig1)(float), float(*trig2)(float))
{
  pos.x() += direction1 * velocity * trig1(angle.y());
  pos.z() += direction2 * velocity * trig2(angle.y());
  adjustInRange<float>(-5, pos.x(), 5);
  adjustInRange<float>(-10.0f, pos.z(), 10.0f);
}
