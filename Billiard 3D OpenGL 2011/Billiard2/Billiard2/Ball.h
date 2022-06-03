#pragma once
#include "Vector4.h"
#include "Drawable.h"

class Ball : public Drawable
{
  static constexpr float speed = 0.08f;
  static constexpr float deceleration = 0.001f;

  float angle = 0;
  float acceleration = 0;
  Color rgb = { 1.0f, 1.0f, 1.0f };
public:
  void color(float r, float g, float b);
  void collide(Ball& other);
  void pull(float acceleration, float angle);
  void update();
  using Drawable::position;
  void position(float x, float z);
  bool isMoving() const;
  void onDraw(GLUquadric* quadric) const override;
};
