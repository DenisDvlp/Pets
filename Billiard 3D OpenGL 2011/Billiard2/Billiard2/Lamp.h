#pragma once
#include "Vector4.h"
#include "Light.h"
#include "Drawable.h"

class Lamp : public Drawable
{
  Light light;
public:
  void onInit() override;
  void onDraw(GLUquadric* quadric) const override;
};

