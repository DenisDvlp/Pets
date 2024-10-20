#include "graphics/Stage.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"

namespace gl {

void Stage::init() {
    constexpr Color backgroundColor{127, 127, 127};
    stage::init(backgroundColor);

    for (Scene* scene : m_scenes) {
        scene->init();
    }
}

void Stage::draw() const {
    static constexpr float viewAngle{65.0f};
    static constexpr float nearDistance{0.01f};
    static constexpr float farDistance{100.0f};
    stage::update(viewAngle, aspect, nearDistance, farDistance);

    PositionBlock;
    transform::position(position);
    transform::rotation(rotation);

    for (const Scene* scene : m_scenes) {
        scene->draw();
    }
}

void Stage::resize(const std::uint16_t width, const std::uint16_t height) {
    if (height != 0) {
        aspect = static_cast<float>(width) / height;
    }
    stage::resize(width, height);
}

void Stage::addScene(Scene& scene) {
    m_scenes.push_back(&scene);
}

} // namespace gl
