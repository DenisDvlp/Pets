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
    // glBegin(GL_QUADS);
    // glVertex3f(-5.0, -2.1f, 2.0);
    // glVertex3f(-5.0, -2.1f, 2.0 + 2.0f);
    // glVertex3f(-5.0 + 2.0f, -2.1f, 2.0 + 2.0f);
    // glVertex3f(-5.0 + 2.0f, -2.1f, 2.0);
    // glEnd();

    {
        MaterialBlock;
        material::reflection(1.0f, 1.0f);
        material::diffusion(1.0f);
        material::ambient(0.0f);
        gluQuadricNormals(ptr, GLU_SMOOTH);
        gluQuadricTexture(ptr, GL_TRUE);
        gluSphere(ptr, 0.068f, 64, 64);
    }
}

} // namespace objects
} // namespace gl
