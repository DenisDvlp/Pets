#include "graphics/Director.hpp"

namespace gl {

void Director::init() {
    buildScene();
    camera.init();
    m_scene.init();
}

void Director::action() const {
    auto guard{camera.block()};
    m_scene.draw();
}

void Director::resize(const std::uint16_t width, const std::uint16_t height) {
    camera.resize(width, height);
}

void Director::buildScene() {
    m_scene.addActor(m_light);
    m_square.position.z() = -1;
    m_scene.addActor(m_square);
}

} // namespace gl
