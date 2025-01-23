#pragma once
#include "graphics/Actor.hpp"

namespace gl {
namespace objects {

class Sphere final : public Actor {
  private:
    void onInit() override;
    void onDraw() const override;
};

} // namespace objects
} // namespace gl
