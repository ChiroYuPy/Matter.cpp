//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Box.h"

Box::Box(const Vector2f &position, const float width, const float height, const float mass, const float friction)
    : Polygon(position, mass, friction, {}), width(width), height(height) {
    vertices = {
        position + Vector2(-width / 2, -height / 2),
        position + Vector2(width / 2, -height / 2),
        position + Vector2(width / 2, height / 2),
        position + Vector2(-width / 2, height / 2)
    };
}

void Box::Update(const float dt) {
    Polygon::Update(dt);

    vertices = {
        position + Vector2(-width / 2, -height / 2),
        position + Vector2(width / 2, -height / 2),
        position + Vector2(width / 2, height / 2),
        position + Vector2(-width / 2, height / 2)
    };
}
