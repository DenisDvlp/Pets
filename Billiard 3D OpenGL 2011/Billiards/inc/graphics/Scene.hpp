#pragma once
#include "Actor.hpp"
#include <vector>

namespace gl {

class Scene {

  public:
    void init();
    void draw() const;
    void addActor(Actor& actor);

  protected:
    std::vector<Actor*> m_actors{};
};

} // namespace gl
