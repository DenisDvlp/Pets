#pragma once
#include "graphics/Actor.hpp"

namespace gl {
namespace objects {

class Light final : public Actor {
  public:
    Light();
    void adjust(const DurationMs milliseconds);
    Movement move{};

  private:
    void onInit() override;
    void onDraw() const override;

  private:
    const unsigned int m_id;
};

} // namespace objects
} // namespace gl
