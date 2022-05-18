#include <algorithm>
#include "Core.h"
#include "Drawing.h"

GLuint  txt[6];
bool Core::hasBallsInGame() const
{
  // We should have at least two balls to consider game as in progress.
  auto isVisible = [](const Ball& ball) {
    return ball.isVisible();
  };

  auto it = std::find_if(balls.cbegin(), balls.cend(), isVisible);
  if(it == balls.cend())
    return false;

  return std::any_of(++it, balls.cend(), isVisible);
}

bool Core::areBallsMoving() const
{
  return std::any_of(balls.cbegin(), balls.cend(), [](const Ball& ball) {
    return ball.isMoving();
    });
}

void Core::init()
{
  table.init();
  lamps.resize(4);
  balls.resize(16);
  // set black color to the first ball
  balls[0].color(127, 85, 85);
  setBallsPositions();
  setLampsPositions();

  initScene();
}

void Core::setBallsPositions()
{
  const float defaultPos[16][2] = {
    { 0.0f, -1.6f },
    { 0.0f, -4.8f },
    { -0.069f, -4.919f },
    { 0.069f, -4.919f },
    { -0.137f, -5.038f },
    { 0.0f, -5.038f },
    { 0.137f, -5.038f },
    { -0.206f, -5.156f },
    { -0.069f, -5.156f },
    { 0.069f, -5.156f },
    { 0.206f, -5.156f },
    { -0.274f, -5.275f },
    { -0.137f, -5.275f },
    { 0.0f, -5.275f },
    { 0.137f, -5.275f },
    { 0.274f, -5.275f },
  };

  size_t i = 0;
  for (auto& ball : balls)
  {
    ball.position(defaultPos[i][0], defaultPos[i][1]);
    ++i;
  }
}

void Core::setLampsPositions()
{
  const float defaultPos[4] = {
    { -0.2f },
    { -1.7f },
    { -3.2f },
    { -4.7f },
  };

  size_t i = 0;
  for (auto& lamp : lamps)
  {
    lamp.position(0, defaultPos[i], 0);
    ++i;
  }
}

void Core::nextBall()
{
  do {
    ++activeBallIndex;
    activeBallIndex %= balls.size();
    camera.setBall(balls[activeBallIndex]);
  } while (!balls[activeBallIndex].isVisible());
}

void Core::prevBall()
{
  do {
    if (activeBallIndex == 0)
      activeBallIndex = balls.size() - 1;
    else
      --activeBallIndex;
    camera.setBall(balls[activeBallIndex]);
  } while (!balls[activeBallIndex].isVisible());
}

void Core::cameraMoveForward()
{
  camera.moveForward();
}

void Core::cameraMoveBackward()
{
  camera.moveBackward();
}

void Core::cameraMoveLeft()
{
  camera.moveLeft();
}

void Core::cameraMoveRight()
{
  camera.moveRight();
}

Camera::Angle Core::cameraAngle() const
{
  return camera.viewAngle();
}

void Core::cameraRotate(float angleX, float angleY)
{
  camera.rotate(angleX, angleY);
}

void Core::cameraResize(int width, int height)
{
  camera.resize(width, height);
}

void Core::ballPull(float acceleration)
{
  balls[activeBallIndex].pull(acceleration, -camera.viewAngle().x);
}

void Core::draw()
{
  clearScene();

  camera.draw();

  //table.draw();

  for (auto& lamp : lamps)
    lamp.draw();

  for (auto& ball : balls)
    ball.draw();
}
