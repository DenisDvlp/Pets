#include "Drawing.h"

void materialReflection(float intensity, float sharpness)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glMaterialfv(GL_FRONT, GL_SPECULAR, color);
  const float shininess = 128.0f * sharpness;
  glMaterialfv(GL_FRONT, GL_SHININESS, &shininess);
}

void materialGlow(float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, color);
}

void materialDiffusion(float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color);
}

void materialAmbient(float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glMaterialfv(GL_FRONT, GL_AMBIENT, color);
}

void lightTurn(int id, bool On)
{
  On ? glEnable(id) : glDisable(id);
}

void lightSpot(int id)
{
  const float xyzs[] = { 0, 0, 0, 1.0f };
  glLightfv(id, GL_POSITION, xyzs);
}

void lightAmbient(int id, float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glLightfv(id, GL_AMBIENT, color);
}

void lightDiffusion(int id, float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glLightfv(id, GL_DIFFUSE, color);
}

void lightReflection(int id, float intensity)
{
  const float color[] = { intensity, intensity, intensity, 1.0f };
  glLightfv(id, GL_SPECULAR, color);
}

void lightSpotAngle(int id, float angle)
{
  glLightf(id, GL_SPOT_CUTOFF, angle);
}

void lightDirection(int id, const float* xyz, bool isSpot)
{
  if (isSpot)
  {
    const float xyzs[] = { 0, 0, 0, 1.0f };
    glLightfv(id, GL_POSITION, xyzs);
    glLightfv(id, GL_SPOT_DIRECTION, xyz);
    return;
  }
  glLightfv(id, GL_POSITION, xyz);
}

void position(const float* xyz)
{
  glTranslatef(xyz[0], xyz[1], xyz[2]);
}
