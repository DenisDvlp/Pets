#pragma once
#include "Camera.hpp"
#include "Scene.hpp"
#include "objects/Light.hpp"
#include "objects/Square.hpp"
#include <vector>

namespace gl {

class Director {
  public:
    void init();
    void adjust();
    void action() const;
    void resize(const std::uint16_t width, const std::uint16_t height);

    Camera camera{};

  protected:
    void buildScene();
    Scene m_scene{};
    objects::Square m_square{};
    objects::Light m_light{};
};

} // namespace gl
