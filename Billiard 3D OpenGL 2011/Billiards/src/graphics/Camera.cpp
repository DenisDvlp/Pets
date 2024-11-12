#include "graphics/Camera.hpp"
#include "graphics/Draw.hpp"
#include <cmath>

namespace gl {

void Camera::init() {
    move.velocity = 2.0f;
    constexpr Color backgroundColor{127, 127, 127};
    camera::init(backgroundColor);
}

void Camera::adjust(const DurationMs milliseconds) {
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
    const float radian = (rotation.y() + angleAdjustment) * pi_v / 180.0f;
    position.x() += -distance * sin(radian);
    position.z() += distance * cos(radian);
}

void Camera::block() const {
    static constexpr float viewAngle{65.0f};
    static constexpr float nearDistance{0.01f};
    static constexpr float farDistance{100.0f};
    camera::clear(viewAngle, aspect, nearDistance, farDistance);
    transform::position(0, 0, -2.0f);
    transform::rotation(rotation);
    transform::position(position);
}

void Camera::resize(const std::uint16_t width, const std::uint16_t height) {
    if (height != 0) {
        aspect = static_cast<float>(width) / height;
    }
    camera::resize(width, height);
}

} // namespace gl
