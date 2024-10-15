#include "graphics/Scene.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"

namespace gl {

void Scene::init() {
    constexpr Color backgroundColor{127, 127, 127};
    scene::init(backgroundColor);

    for (SceneObject* sceneObject : m_sceneObjects) {
        sceneObject->init();
    }
}

void Scene::draw() const {
    static constexpr float viewAngle{65.0f};
    static constexpr float nearDistance{0.01f};
    static constexpr float farDistance{100.0f};
    scene::update(viewAngle, aspect, nearDistance, farDistance);

    for (const SceneObject* sceneObject : m_sceneObjects) {
        sceneObject->draw();
    }
}
void Scene::resize(const std::uint16_t width, const std::uint16_t height) {
    aspect = static_cast<float>(width) / height;
    scene::resize(width, height);
}

void Scene::addSceneObject(SceneObject& sceneObject) { m_sceneObjects.push_back(&sceneObject); }

} // namespace gl
