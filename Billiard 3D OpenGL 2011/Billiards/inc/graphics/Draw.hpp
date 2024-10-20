#pragma once
#include <cstdint>
#include <windows.h>

namespace gl {

namespace camera {

// backgroundColor [red, green, blue, alpha]
// e.g. 0xFF00AAFF
void init(const std::uint8_t* backgroundColor);

// angle - The field of view angle, in degrees, in the y-direction.
// aspect - The aspect ratio is the ratio of width / height.
// nearDistance - The distance from the viewer to the near clipping plane >0.
// farDistance - The distance from the viewer to the far clipping plane >0.
void clear(const float angle, const float aspect, const float nearDistance, const float farDistance);

// width - width of the window.
// height - height of the window.
void resize(const std::uint16_t width, const std::uint16_t height);

} // namespace camera

namespace color {

// array of 4 [red, green, blue, alpha]
// e.g. 0xFF00AAFF
void rgba(const std::uint8_t* color);

// array of 3 [red, green, blue, 255]
// e.g. 0xFF00AA
void rgb(const std::uint8_t* color);

} // namespace color

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

unsigned int availableId();

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

namespace figure {

void sphere(const float radius, const int verPolygons, const int horPolygons);

void cylinder(const float baseRadius, const float topRadius, const float height, const int verPolygons,
              const int horPolygons);
void disk(const float innerRadius, const float outerRadius, const int verPolygons, const int horPolygons);

void square(const float sideLength, const int verPolygons, const int horPolygons);

} // namespace figure

namespace guard {

struct MaterialGuard {
    MaterialGuard();
    ~MaterialGuard();
};

struct MatrixGuard {
    MatrixGuard();
    ~MatrixGuard();
};

#define MaterialBlock gl::guard::MaterialGuard glMaterialGuard
#define PositionBlock gl::guard::MatrixGuard glMatrixGuard

} // namespace guard

} // namespace gl
