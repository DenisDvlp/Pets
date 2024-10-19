#include "objects/Square.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"
#include <gl/gl.h>
#include <gl/glu.h>

namespace gl {
namespace objects {
auto ptr{gluNewQuadric()};

void Square::onInit() {}

void Square::onDraw() const {
    constexpr Color color{255, 0, 255};
    color::rgb(color);
    MaterialBlock;
    material::reflection(1.0f, 1.0f);
    material::diffusion(1.0f);
    material::ambient(0.0f);
    figure::square(1.0f, 10, 10);
}

} // namespace objects
} // namespace gl
