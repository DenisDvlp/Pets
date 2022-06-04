#pragma once
#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>

// intensity [0..1]
// sharpness [0..1]
void materialReflection(float intensity, float sharpness);

// intensity [0..1]
void materialGlow(float intensity);

// intensity [0..1]
void materialDiffusion(float intensity);

// intensity [0..1]
void materialAmbient(float intensity);

// id - light ID
// On - turn on or turn off
void lightTurn(int id, bool On);

// id - light ID
// represent light as a spot
void lightSpot(int id);

// id - light ID
// intensity [0..1]
void lightAmbient(int id, float intensity);

// id - light ID
// intensity [0..1]
void lightDiffusion(int id, float intensity);

// id - light ID
// intensity [0..1]
void lightReflection(int id, float intensity);

// id - light ID
// angle [0..360]
void lightSpotAngle(int id, float angle);

// id - light ID
// xyz[3]
// isSpot - is light a spot or sun
void lightDirection(int id, const float* xyz, bool isSpot);

// xyz[3]
void position(const float* xyz);

struct MaterialGuard {
  MaterialGuard() { glPushAttrib(GL_LIGHTING_BIT); }
  ~MaterialGuard() { glPopAttrib(); }
};

struct MatrixGuard {
  MatrixGuard() { glPushMatrix(); }
  ~MatrixGuard() { glPopMatrix(); }
};

#define materialBlock MaterialGuard guard
#define positionBlock MatrixGuard guard