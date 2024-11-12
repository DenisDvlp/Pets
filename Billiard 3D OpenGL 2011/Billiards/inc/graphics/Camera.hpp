#pragma once
#include "Types.hpp"

namespace gl {

class Camera {
  public:
    void init();
    void adjust(const DurationMs milliseconds);
    void block() const;
    void resize(const std::uint16_t width, const std::uint16_t height);

    Movement move{};
    Position position{};
    Rotation rotation{};

  protected:
    float aspect{1};
};

} // namespace gl
