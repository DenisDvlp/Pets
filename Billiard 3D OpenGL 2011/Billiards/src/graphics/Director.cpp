#include "graphics/Director.hpp"

namespace gl {

void Director::init() {
    buildScenes();
    m_stage.init();
}

void Director::draw() const {
    m_stage.draw();
}

void Director::resize(const std::uint16_t width, const std::uint16_t height) {
    m_stage.resize(width, height);
}

void Director::buildScenes() {
    Scene& scene{m_scenes.emplace_back()};

    scene.addActor(m_light);
    m_square.position.z() = -1;
    scene.addActor(m_square);

    m_stage.addScene(scene);
}

} // namespace gl
