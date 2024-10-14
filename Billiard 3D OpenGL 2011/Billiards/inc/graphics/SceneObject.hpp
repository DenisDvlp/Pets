#pragma once
#include "graphics/Types.hpp"

namespace gl {

class SceneObject {
  public:
    void init();
    void draw() const;

    Position position{};
    Rotation rotation{};
    bool visible{true};

  private:
    virtual void onDraw() const = 0;
    virtual void onInit() const = 0;
};

} // namespace gl
