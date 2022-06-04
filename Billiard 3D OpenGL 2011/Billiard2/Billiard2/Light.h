#pragma once
#include "Vector4.h"
#include "Drawable.h"

class Light : public Drawable
{
  const unsigned int id;
  const bool isSpot;
  Direction spotDirection;
public:
  Light(bool isSpot = true);
  ~Light();
  void enable(bool enabled);
  void ambient(float intensity);
  void diffusion(float intensity);
  void specular(float intensity);
  void direction(float x, float y, float z);
  void cutoffAngle(float angle);
  void onDraw(GLUquadric* quadric) const override;
};

