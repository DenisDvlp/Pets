#include "graphics/Director.hpp"
#include "graphics/Types.hpp"
#include <chrono>

namespace gl {

void Director::init() {
    buildScene();
    camera.init();
    m_scene.init();
}

static DurationMs millisecondsSinceLastAdjustment() {
    using namespace std::chrono;
    auto now = duration_cast<milliseconds>(steady_clock::now().time_since_epoch()).count();
    static auto last{now};
    auto result{now - last};
    last = now;
    return result;
}

void Director::adjust() {
    const DurationMs timespan{millisecondsSinceLastAdjustment()};
    camera.adjust(timespan);
    m_light.adjust(timespan);
}

void Director::action() const {
    camera.block();
    m_scene.draw();
}

void Director::resize(const std::uint16_t width, const std::uint16_t height) {
    camera.resize(width, height);
}

void Director::buildScene() {
    m_light.rotation.x() = 270;
    m_light.position.y() = 3;
    m_light.position.x() = 3;
    m_scene.addActor(m_light);

    // m_square[0].rotation.y() = 180;
    // m_square[0].position.z() = -1;

    // m_square[1].rotation.y() = 0;
    // m_square[1].position.z() = 1;

    // m_square[2].rotation.y() = 270;
    // m_square[2].position.x() = -1;

    // m_square[3].rotation.y() = 90;
    // m_square[3].position.x() = 1;

    // m_square[4].rotation.x() = 90;
    // m_square[4].position.y() = 1;

    // m_square[5].rotation.x() = 270;
    // m_square[5].position.y() = -1;

    // for (size_t i = 0; i < 6; i++) {
    //     m_scene.addActor(m_square[i]);
    // }

    m_scene.addActor(m_sphere);
}

} // namespace gl
