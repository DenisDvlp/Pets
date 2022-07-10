#include "Lamp.h"
#include "Drawing.h"

void Lamp::onInit()
{
  light.enable(true);
  light.position(0, 0.2f, 0);
  light.direction(0, -1.0f, 0);
  light.ambient(0.0f);
  light.diffusion(0.2f);
  light.specular(1.0f);
  light.cutoffAngle(70.0f);
}

void Lamp::onDraw(GLUquadric* quadric) const
{
  light.draw(quadric);

  glRotatef(-90, 1, 0, 0);
  glColor3f(0.004f, 0.306f, 0.212f);
  {
    materialBlock;
    materialReflection(1.0f, 1.0f);
    gluCylinder(quadric, 0.7f, 0.2f, 0.6f, 64, 32);
  }
  {
    positionBlock;
    glTranslatef(0, 0, 0.6f);
    gluDisk(quadric, 0.1f, 0.2f, 64, 32);
  }
  {
    materialBlock;
    materialGlow(1.0f);
    gluCylinder(quadric, 0.69f, 0.19f, 0.59f, 32, 1);
  }
}
