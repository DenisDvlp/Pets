#pragma once
#include "Types.hpp"

namespace gl {

class SceneObject {
  public:
    void init();
    void draw() const;

    Position position{};
    Rotation rotation{};
    bool visible{true};

  private:
    virtual void onInit() = 0;
    virtual void onDraw() const = 0;
};

} // namespace gl
