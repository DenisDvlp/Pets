#include "graphics/Camera.hpp"
#include "graphics/Types.hpp"

namespace gl {

void Camera::init() {
    constexpr Color backgroundColor{127, 127, 127};
    camera::init(backgroundColor);
}

guard::MatrixGuard Camera::block() const {
    static constexpr float viewAngle{65.0f};
    static constexpr float nearDistance{0.01f};
    static constexpr float farDistance{100.0f};
    camera::clear(viewAngle, aspect, nearDistance, farDistance);

    guard::MatrixGuard guard;
    transform::position(position);
    transform::rotation(rotation);

    return guard;
}

void Camera::resize(const std::uint16_t width, const std::uint16_t height) {
    if (height != 0) {
        aspect = static_cast<float>(width) / height;
    }
    camera::resize(width, height);
}

} // namespace gl
