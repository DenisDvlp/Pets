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
