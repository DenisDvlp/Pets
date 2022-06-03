#include "Light.h"
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

static auto lastLightId = GL_LIGHT0;

Light::Light(bool isSpot /*= true*/) : lightId(lastLightId++)
{
  pos.a() = float(isSpot);
  enable(true);
}

Light::~Light()
{
  --lastLightId;
}

void Light::enable(bool enabled)
{
  enabled ? glEnable(lightId) : glDisable(lightId);
}

void Light::ambient(float r, float g, float b)
{
  GLfloat ambientColor[] = { r, g, b, 1.0f };
  glLightfv(lightId, GL_AMBIENT, ambientColor);
}

void Light::diffusion(float r, float g, float b)
{
  GLfloat diffusionColor[] = { r, g, b, 1.0f };
  glLightfv(lightId, GL_DIFFUSE, diffusionColor);
}

void Light::specular(float r, float g, float b)
{
  GLfloat specularColor[] = { r, g, b, 1.0f };
  glLightfv(lightId, GL_SPECULAR, specularColor);
}

void Light::direction(float x, float y, float z)
{
  spotDirection.set(x, y, z);
  glLightfv(lightId, GL_SPOT_DIRECTION, spotDirection);
}

void Light::cutoffAngle(float angle)
{
  glLightf(lightId, GL_SPOT_CUTOFF, angle);
}

void Light::onDraw(GLUquadric* quadric) const
{
  glTranslatef(-pos.x(), -pos.y(), -pos.z());
  glLightfv(lightId, GL_POSITION, pos);
  glLightfv(lightId, GL_SPOT_DIRECTION, spotDirection);
}
