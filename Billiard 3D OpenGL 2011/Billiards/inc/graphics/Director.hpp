#pragma once
#include "Scene.hpp"
#include "Stage.hpp"
#include "objects/Light.hpp"
#include "objects/Square.hpp"
#include <vector>

namespace gl {

class Director {
  public:
    void init();
    void draw() const;
    void resize(const std::uint16_t width, const std::uint16_t height);

  protected:
    void buildScenes();
    Stage m_stage{};
    std::vector<Scene> m_scenes{};
    objects::Square m_square{};
    objects::Light m_light{};
};

} // namespace gl
