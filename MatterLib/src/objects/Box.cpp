//
// Created by adrian on 26/02/25.
//

#include "MATTER/objects/Box.h"

Box::Box(const Vector2f &position, const float width, const float height) : Polygon(position, {
    position + Vector2(-width / 2, -height / 2),
    position + Vector2(width / 2, -height / 2),
    position + Vector2(width / 2, height / 2),
    position + Vector2(-width / 2, height / 2)
}), width(width), height(height) {}

void Box::update(const float dt) {
    Polygon::update(dt);

    vertices = {
        position + Vector2(-width / 2, -height / 2),
        position + Vector2(width / 2, -height / 2),
        position + Vector2(width / 2, height / 2),
        position + Vector2(-width / 2, height / 2)
    };
}
