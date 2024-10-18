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
    constexpr Color color{0xFF00AA};
    color::rgb(color);
    MaterialBlock;
    material::reflection(1.0f, 1.0f);
    material::diffusion(1.0f);
    material::ambient(0.0f);
    glBegin(GL_QUADS);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(0, 1, 0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1, 0, 0);
    glVertex3f(1, 1, 0);
    glVertex3f(2, 1, 0);
    glVertex3f(2, 0, 0);
    glEnd();

    {
        // MaterialBlock;
        // material::reflection(1.0f, 1.0f);
        // material::diffusion(1.0f);
        // material::ambient(0.0f);
        // figure::cylinder(0.7f, 0.2f, 0.6f, 64, 32);
    }
}

} // namespace objects
} // namespace gl
