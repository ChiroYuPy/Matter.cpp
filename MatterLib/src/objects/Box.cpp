//
// Created by adrian on 26/02/25.
//

#include "MATTER/objects/Box.h"

Box::Box(const Vector2f &position, const float width, const float height) : Polygon(position, {
        Vector2f(-width / 2, -height / 2),
        Vector2f(width / 2, -height / 2),
        Vector2f(width / 2, height / 2),
        Vector2f(-width / 2, height / 2)
    }),
      width(width), height(height) {}

void Box::update(const float dt) {
    Polygon::update(dt);
}

float Box::getWidth() const {
    return width;
}

float Box::getHeight() const {
    return height;
}
