#include "objects/Light.hpp"
#include "graphics/Draw.hpp"

namespace gl {
namespace objects {

Light::Light() : m_id{light::availableId()} {}

void Light::onInit() {
    light::turn(m_id, true);
    light::ambient(m_id, 0.5f);
    light::diffusion(m_id, 0.5f);
    light::reflection(m_id, 1.0f);
    light::spotAngle(m_id, 180);
}

void Light::onDraw() const {
    light::direction(m_id, rotation, false);
}

} // namespace objects
} // namespace gl
