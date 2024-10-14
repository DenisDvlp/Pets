#pragma once
#include <windows.h>

namespace gl {

namespace material {

// intensity [0..1]
// sharpness [0..1]
void reflection(float intensity, float sharpness);

// intensity [0..1]
void glow(float intensity);

// intensity [0..1]
void diffusion(float intensity);

// intensity [0..1]
void ambient(float intensity);

} // namespace material

namespace light {

// id - light ID
// On - turn on or turn off
void turn(int id, bool on);

// id - light ID
// intensity [0..1]
void ambient(int id, float intensity);

// id - light ID
// intensity [0..1]
void diffusion(int id, float intensity);

// id - light ID
// intensity [0..1]
void reflection(int id, float intensity);

// id - light ID
// angle [0..360]
void spotAngle(int id, float angle);

// id - light ID
// xyz[3]
// isSpot - is light a spot or sun
void direction(int id, const float* xyz, bool isSpot);

} // namespace light

namespace transform {

// xyz[3]
void position(const float* xyz);

// x, y, z
void position(float x, float y, float z);

// xyz[3] angles around all pivots
void rotation(const float* xyz);

// angle around x pivot
void rotationX(const float angle);

// angle around y pivot
void rotationY(const float angle);

// angle around z pivot
void rotationZ(const float angle);

} // namespace transform

namespace guard {

struct MaterialGuard {
    MaterialGuard();
    ~MaterialGuard();
};

struct MatrixGuard {
    MatrixGuard();
    ~MatrixGuard();
};

#define MateriaBlock gl::guard::MaterialGuard glMaterialGuard
#define PositionBlock gl::guard::MatrixGuard glMatrixGuard

} // namespace guard

} // namespace gl
