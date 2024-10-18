#pragma once
#include "graphics/SceneObject.hpp"

namespace gl {
namespace objects {

class Square final : public SceneObject {

  private:
    void onInit() override;
    void onDraw() const override;
};

} // namespace objects
} // namespace gl
