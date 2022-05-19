#pragma once
#include "Position.h"
#include "QuadricPtr.h"

class Lamp
{
  static unsigned int lastLightId;
  const unsigned int lightId;
  QuadricPtr quadric;
  Position pos;
public:
  Lamp();
  ~Lamp() { --lastLightId; }
  void position(float x, float y, float z);
  void draw();
};

