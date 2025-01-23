#include "objects/Sphere.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"

namespace gl {
namespace objects {

void Sphere::onInit() {}

void Sphere::onDraw() const {
    constexpr Color color{0xFF0000};
    color::rgb(color);
    MaterialBlock;
    material::reflection(1.0f, 1.0f);
    material::diffusion(0.5f);
    material::ambient(0.5f);
    figure::sphere(2, 50, 50);
}

} // namespace objects
} // namespace gl
