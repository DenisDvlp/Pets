#pragma once
#include <vector>
#include "Ball.h"
#include "Camera.h"
#include "Lamp.h"
#include "Table.h"

class Core
{
  std::vector<Ball> balls;
  std::vector<Lamp> lamps;
  Camera camera;
  Table table;
  size_t activeBallIndex;
public:
  bool hasBallsInGame() const;
  bool areBallsMoving() const;
  void init();
  void setBallsPositions();
  void setLampsPositions();
  void nextBall();
  void prevBall();
  void cameraMoveForward();
  void cameraMoveBackward();
  void cameraMoveLeft();
  void cameraMoveRight();
  Camera::Angle cameraAngle() const;
  void cameraRotate(float angleX, float angleY);
  void cameraResize(int width, int height);
  void ballPull(float acceleration);
  void draw();
};

