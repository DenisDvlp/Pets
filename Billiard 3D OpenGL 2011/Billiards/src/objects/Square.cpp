#include "objects/Square.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"

namespace gl {
namespace objects {

void Square::onInit() {}

void Square::onDraw() const {
    constexpr Color color{0, 0, 255};
    color::rgb(color);
    MaterialBlock;
    material::reflection(1.0f, 1.0f);
    material::diffusion(0.5f);
    material::ambient(0.5f);
    figure::square(2, 50, 50);
}

} // namespace objects
} // namespace gl
