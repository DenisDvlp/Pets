#pragma once
#include "Drawable.h"
class Plate : public Drawable
{
  void onDraw(GLUquadric* quadric) const override;
};

