#include <algorithm>
#include "Core.h"
#include "Utils.h"

Core::Core()
{
  scene.setCamera(camera);
  scene.addDrawable(sunLight);
  scene.addDrawable(table);
  scene.addDrawables(lamps);
  scene.addDrawables(balls);
  //scene.addDrawable(plate);
}

bool Core::hasBallsInGame() const
{
  // We should have at least two balls to consider game as in progress.
  auto isVisible = [](const Ball& ball) {
    return ball.visible();
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
  scene.init();

  // set black color to the first ball
  balls[0].color(0.5f, 0.33f, 0.33f);
  setBallsPositions();
  setLampsPositions();

  sunLight.enable(true);
  sunLight.direction(0, -1.0f, 0);
  sunLight.ambient(0.15f);
  sunLight.diffusion(0.5f);
  sunLight.specular(0.6f);
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
  float angle = 10;
  for (auto& ball : balls)
  {
    ball.position(defaultPos[i][0], defaultPos[i][1]);
    ball.pull(1.0f, angle);
    angle += 10;
    ++i;
  }
}

void Core::setLampsPositions()
{
  float distance = -1.05f;
  for (auto& lamp : lamps)
  {
    lamp.position(0, 0, distance);
    distance -= 1.7f;
  }
}

void Core::nextBall()
{
  changeBall(true);
}

void Core::prevBall()
{
  changeBall(false);
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

Angle Core::cameraAngle() const
{
  return camera.viewAngle();
}

void Core::cameraRotate(float angleX, float angleY)
{
  camera.rotate(angleX, angleY);
}

void Core::sceneResize(int width, int height)
{
  scene.resize(width, height);
}

void Core::ballPull(float acceleration)
{
  balls[activeBallIndex].pull(acceleration, -camera.viewAngle().x());
}

void Core::update(milliseconds ms)
{
  for (auto& ball : balls)
  {
    ball.update(ms);
  }  
}

void Core::draw()
{
  scene.draw();
}

// isNext - `true` for the next and `false` for the previous ball.
void Core::changeBall(bool isNext)
{
  do {
    activeBallIndex += (isNext ? 1 : -1);
    adjustInLoop<size_t>(0, activeBallIndex, balls.size() - 1);
    camera.setBall(balls[activeBallIndex]);
  } while (!balls[activeBallIndex].visible());
}
