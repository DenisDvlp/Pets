#pragma once
#include "SceneObject.hpp"
#include <cstdint>
#include <vector>

namespace gl {

class Scene {

  public:
    void init();
    void draw() const;
    void addSceneObject(SceneObject& drawable);
    void resize(const std::uint16_t width, const std::uint16_t height);

  protected:
    std::vector<SceneObject*> m_sceneObjects;
    float aspect;
};

} // namespace gl
