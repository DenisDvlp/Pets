#pragma once
#include <vector>
#include "Ball.h"
#include "Camera.h"
#include "Lamp.h"
#include "Table.h"
#include "Plate.h"
#include "Scene.h"

class Core
{
  std::vector<Ball> balls{16};
  std::vector<Lamp> lamps{4};
  Camera camera;
  Table table;
  Plate plate;
  size_t activeBallIndex;
  Scene scene;
  Light sunLight = false;
public:
  Core();
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
  Angle cameraAngle() const;
  void cameraRotate(float angleX, float angleY);
  void sceneResize(int width, int height);
  void ballPull(float acceleration);
  void update(milliseconds ms);
  void draw();
private:
  void changeBall(bool isNext);
};

