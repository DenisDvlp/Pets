#pragma once
#include "Vector4.h"
#include "Drawable.h"

using GLuint = unsigned int;

class Table : public Drawable
{
  GLuint  textures[3];
  GLuint tableList;
public:
  void onInit() override;
  void onDraw(GLUquadric* quadric) const override;
private:
  void createTable(GLuint texture);
  void drawTable(const GLuint* texture, GLUquadric* quadratic) const;
};

