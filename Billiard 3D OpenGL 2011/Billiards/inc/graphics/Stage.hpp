#pragma once
#include "Scene.hpp"
#include "Types.hpp"
#include <vector>

namespace gl {

class Stage {
  public:
    void init();
    void draw() const;
    void resize(const std::uint16_t width, const std::uint16_t height);
    void addScene(Scene& scene);

    Position position{};
    Rotation rotation{};

  protected:
    std::vector<Scene*> m_scenes{};
    float aspect{1};
};

} // namespace gl
