#pragma once
#include "Vector4.h"
#include "Drawable.h"

using GLuint = unsigned int;

class Table : public Drawable
{
  GLuint  textures[3];
public:
  void onInit() override;
  void onDraw(GLUquadric* quadric) const override;
};

