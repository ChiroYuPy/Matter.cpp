//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Box.h"

Box::Box(const Vector2& position, float width, float height, float mass, float friction)
    : Polygon(position, mass, friction, {}), width(width), height(height) {

    vertices = {
        position + Vector2(-width / 2, -height / 2),
        position + Vector2(width / 2, -height / 2),
        position + Vector2(width / 2, height / 2),
        position + Vector2(-width / 2, height / 2)
    };
}

void Box::Update(float dt) {
    Polygon::Update(dt);

    vertices = {
        position + Vector2(-width / 2, -height / 2),
        position + Vector2(width / 2, -height / 2),
        position + Vector2(width / 2, height / 2),
        position + Vector2(-width / 2, height / 2)
    };
}
