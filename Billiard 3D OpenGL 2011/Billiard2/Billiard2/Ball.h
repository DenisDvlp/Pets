#pragma once
#include "Vector4.h"
#include "Drawable.h"
#include <chrono>

using namespace std::chrono;
using namespace std::chrono_literals;

class Ball : public Drawable
{
  static constexpr float deceleration = -0.15f;

  float angle = 0;
  float velocity = 0;
  Color rgb = { 0.925f, 0.937f, 0.855f };
public:
  void color(float r, float g, float b);
  void collide(Ball& other);
  void pull(float velocity, float angle);
  void collide(float angle);
  void update(milliseconds ms);
  using Drawable::position;
  void position(float x, float z);
  bool isMoving() const;
  void onDraw(GLUquadric* quadric) const override;
};
