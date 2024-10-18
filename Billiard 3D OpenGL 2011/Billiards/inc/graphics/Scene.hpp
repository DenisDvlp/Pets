#pragma once
#include "Actor.hpp"
#include <cstdint>
#include <vector>

namespace gl {

class Scene {

  public:
    void init();
    void draw() const;
    void addActor(Actor& actor);
    void resize(const std::uint16_t width, const std::uint16_t height);

  protected:
    void onInit();

  protected:
    std::vector<Actor*> m_actors;
    float aspect;
};

} // namespace gl
