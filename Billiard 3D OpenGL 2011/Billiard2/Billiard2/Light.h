#pragma once
#include "Vector4.h"
#include "Drawable.h"

class Light : public Drawable
{
  const unsigned int lightId;
  Direction spotDirection;
public:
  Light(bool isSpot = true);
  ~Light();
  void enable(bool);
  void ambient(float r, float g, float b);
  void diffusion(float r, float g, float b);
  void specular(float r, float g, float b);
  void direction(float x, float y, float z);
  void cutoffAngle(float angle);
  void onDraw(GLUquadric* quadric) const override;
};

