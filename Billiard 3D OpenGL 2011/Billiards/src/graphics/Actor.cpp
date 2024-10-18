#include "graphics/Actor.hpp"
#include "graphics/Draw.hpp"

namespace gl {

void Actor::init() { onInit(); }

void Actor::draw() const {
    if (visible) {
        PositionBlock;
        transform::position(position);
        transform::rotation(rotation);
        onDraw();
    }
}

} // namespace gl
