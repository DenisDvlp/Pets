#include "Light.h"
#include "Drawing.h"

static auto lastLightId = GL_LIGHT0;

Light::Light(bool isSpot /*= true*/) :
  id(lastLightId++), isSpot(isSpot)
{}

Light::~Light()
{
  --lastLightId;
}

void Light::enable(bool enabled)
{
  lightTurn(id, enabled);
}

void Light::ambient(float intensity)
{
  lightAmbient(id, intensity);
}

void Light::diffusion(float intensity)
{
  lightDiffusion(id, intensity);
}

void Light::specular(float intensity)
{
  lightReflection(id, intensity);
}

void Light::direction(float x, float y, float z)
{
  if (isSpot)
    spotDirection.set(x, y, z);
  else
    spotDirection.set(-x, -y, -z, 0); // Last param is a hack. See ::lightDirection.
}

void Light::cutoffAngle(float angle)
{
  lightSpotAngle(id, angle);
}

void Light::onDraw(GLUquadric* quadric) const
{
  lightDirection(id, spotDirection, isSpot);
}
