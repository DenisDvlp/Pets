#include "graphics/SceneObject.hpp"
#include "graphics/Drawing.hpp"

namespace gl {

void SceneObject::init() { onInit(); }

void SceneObject::draw() const {
    if (visible) {
        PositionBlock;
        transform::position(position);
        onDraw();
    }
}

} // namespace gl
