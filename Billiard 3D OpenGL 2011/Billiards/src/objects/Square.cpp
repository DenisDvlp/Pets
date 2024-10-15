#include "objects/Square.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"
#include <gl/gl.h>

namespace gl {
namespace objects {

void Square::onInit() {}

void Square::onDraw() const {
    constexpr Color color{0xFF00AA};
    color::rgb(color);
    glBegin(GL_QUADS);
    glVertex3f(-5.0, -2.1f, 2.0);
    glVertex3f(-5.0, -2.1f, 2.0 + 2.0f);
    glVertex3f(-5.0 + 2.0f, -2.1f, 2.0 + 2.0f);
    glVertex3f(-5.0 + 2.0f, -2.1f, 2.0);
    glEnd();
}

} // namespace objects
} // namespace gl
