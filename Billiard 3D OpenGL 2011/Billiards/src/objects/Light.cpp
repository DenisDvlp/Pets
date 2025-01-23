#include "objects/Light.hpp"
#include "graphics/Draw.hpp"
#include <cmath>

namespace gl {
namespace objects {

Light::Light() : m_id{light::availableId()} {}

void Light::onInit() {
    light::turn(m_id, true);
    light::ambient(m_id, 0.5f);
    light::diffusion(m_id, 1.0f);
    light::reflection(m_id, 1.0f);
    // light::spotAngle(m_id, 10.0f);
}

void Light::onDraw() const {
    static constexpr float xyz[] = {0.0f, 0.0f, -1.0f};
    light::direction(m_id, xyz, false);
    color::rgb(Color{255, 0, 0});
    PositionBlock;
    transform::rotationX(180);
    figure::cylinder(0, 0.2f, 0.2f, 10, 10);
}

void Light::adjust(const DurationMs milliseconds) {
    if (!(move.forward ^ move.backward) && !(move.left ^ move.right)) {
        return;
    }

    const float angleAdjustment{[this]() -> float {
        float angle{0.0f};
        if (!(move.left ^ move.right)) {
            if (move.forward) {
                return 0.0f;
            }
            return 180.f;
        }

        if (!(move.forward ^ move.backward)) {
            if (move.left) {
                return -90.0f;
            }
            return 90.0f;
        }

        if (move.forward) {
            if (move.left) {
                return -45.0f;
            }
            return 45.0f;
        }

        if (move.left) {
            return 225.0f;
        }
        return 135.0f;
    }()};

    static constexpr float pi_v = static_cast<float>(3.14159265358979323846);
    const float distance = move.velocity * milliseconds / 1000.f;
    const float radian = angleAdjustment * pi_v / 180.0f;
    position.x() += -distance * sin(radian);
    position.z() += distance * cos(radian);
}

} // namespace objects
} // namespace gl
