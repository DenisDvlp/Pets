#pragma once
#include "Position.h"
#include "QuadricPtr.h"

using GLuint = unsigned int;

class Table
{
  QuadricPtr quadric;
  Position pos;

  GLuint  textures[3];
public:
  void init();
  void position(float x, float y, float z);
  void draw();
};
