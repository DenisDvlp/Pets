#include "graphics/Scene.hpp"
#include "graphics/Draw.hpp"
#include "graphics/Types.hpp"

namespace gl {

void Scene::init() {
    for (Actor* actor : m_actors) {
        actor->init();
    }
}

void Scene::draw() const {
    for (const Actor* actor : m_actors) {
        actor->draw();
    }
}

void Scene::addActor(Actor& actor) {
    m_actors.push_back(&actor);
}

} // namespace gl
