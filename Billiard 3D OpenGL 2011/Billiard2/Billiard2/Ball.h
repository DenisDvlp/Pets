#pragma once
#include "Position.h"
#include "QuadricPtr.h"

class GLUquadric;
using GLubyte = unsigned char;

class Ball
{
  static constexpr float speed = 0.08f;
  static constexpr float deceleration = 0.001f;

  QuadricPtr quadric;
  Position pos = { 0, -1.932f, 0 };
  float angle = 0;
  float acceleration = 0;
  GLubyte rgb[3] = { 255, 255, 255 };
  bool visible = true;
public:
  void color(GLubyte r, GLubyte g, GLubyte b);
  void collide(Ball& other);
  void pull(float acceleration, float angle);
  void update();
  const Position& position() const;
  void position(float x, float z);
  void position(float x, float y, float z);
  bool isVisible() const;
  bool isMoving() const;
  void draw();
};
