#pragma once
#include "Scene.hpp"
#include "Types.hpp"
#include "graphics/Draw.hpp"
#include <vector>

namespace gl {

class Camera {
  public:
    void init();
    [[nodiscard]] guard::MatrixGuard block() const;
    void resize(const std::uint16_t width, const std::uint16_t height);

    Position position{};
    Rotation rotation{};

  protected:
    float aspect{1};
};

} // namespace gl
