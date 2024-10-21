#include "objects/Square.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"
#include <gl/gl.h>
#include <gl/glu.h>

namespace gl {
namespace objects {

void Square::onInit() {}

void Square::onDraw() const {
    constexpr Color color{0, 0, 255};
    color::rgb(color);
    MaterialBlock;
    material::reflection(1.0f, 1.0f);
    material::diffusion(1.0f);
    material::ambient(1.0f);
    figure::square(2, 50, 50);
}

} // namespace objects
} // namespace gl
