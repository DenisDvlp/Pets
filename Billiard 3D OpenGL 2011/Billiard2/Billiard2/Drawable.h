#pragma once
#include "Vector4.h"

class GLUquadric;

class Drawable
{
protected:
  Position pos;
  bool isVisible = true;
private:
  virtual void onDraw(GLUquadric* quadric) const = 0;
public:
  void visible(bool isVisible);
  bool visible() const;
  void position(float x, float y, float z);
  void position(const Position& pos);
  Position& position();
  const Position& position() const;
  void init();
  virtual void onInit() {};
  void draw(GLUquadric* quadric) const;
};

