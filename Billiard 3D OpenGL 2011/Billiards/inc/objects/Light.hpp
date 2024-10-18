#pragma once
#include "graphics/SceneObject.hpp"

namespace gl {
namespace objects {

class Light final : public SceneObject {
  public:
    Light();

  private:
    void onInit() override;
    void onDraw() const override;

  private:
    const unsigned int m_id;
};

} // namespace objects
} // namespace gl
