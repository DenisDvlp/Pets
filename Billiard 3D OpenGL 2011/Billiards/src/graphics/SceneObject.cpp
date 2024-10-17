#include "graphics/SceneObject.hpp"
#include "graphics/Draw.hpp"

namespace gl {

void SceneObject::init() { onInit(); }

void SceneObject::draw() const {
    if (visible) {
        PositionBlock;
        transform::position(position);
        transform::rotation(rotation);
        onDraw();
    }
}

} // namespace gl
