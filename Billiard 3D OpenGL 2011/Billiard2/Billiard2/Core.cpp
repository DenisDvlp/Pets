#include <algorithm>
#include "Core.h"

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
  sunLight.enable(true);
  sunLight.position(0.0f, 1.0f, 0.0f);
  sunLight.ambient(0.1f, 0.1f, 0.1f);
  sunLight.diffusion(0.5f, 0.5f, 0.5f);
  sunLight.specular(0.3f, 0.3f, 0.3f);

  table.init();
  table.visible(false);
  lamps.resize(4);
  balls.resize(16);
  // set black color to the first ball
  balls[0].color(127 / 255.0f, 85 / 255.0f, 85 / 255.0f);
  setBallsPositions();
  setLampsPositions();

  scene.setCamera(camera);
  scene.addDrawable(sunLight);
  scene.addDrawable(table);
  scene.addDrawable(plate);
  scene.addDrawables(lamps);
  scene.addDrawables(balls);

  scene.init();

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
    lamp.position(0, 0, defaultPos[i]);
    ++i;
  }
}

void Core::nextBall()
{
  do {
    ++activeBallIndex;
    activeBallIndex %= balls.size();
    camera.setBall(balls[activeBallIndex]);
  } while (!balls[activeBallIndex].visible());
}

void Core::prevBall()
{
  do {
    if (activeBallIndex == 0)
      activeBallIndex = balls.size() - 1;
    else
      --activeBallIndex;
    camera.setBall(balls[activeBallIndex]);
  } while (!balls[activeBallIndex].visible());
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

void Core::update()
{
}

void Core::draw()
{
  scene.draw();
}
