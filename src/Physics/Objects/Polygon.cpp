//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Polygon.h"

Polygon::Polygon(const Vector2f &position, const std::vector<Vector2f> &verts)
    : RigidBody(position), vertices(verts) {
}

void Polygon::update(const float dt) {
    RigidBody::update(dt);
}

AABB Polygon::getAABB() const {
    if (rotatedVertices.empty()) return {Vector2f(), Vector2f()};

    Vector2 min = rotatedVertices[0];
    Vector2 max = rotatedVertices[0];

    for (const auto &v: rotatedVertices) {
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
    }

    return {min, max};
}

std::vector<Vector2f> Polygon::getVertices() const {


    rotatedVertices.clear();

    const Vector2f center = getPosition();

    for (const auto &v : vertices) {
        const Vector2f translated = v - center;

        const float cos = std::cos(angle);
        const float sin = std::sin(angle);
        float const xNew = translated.x * cos - translated.y * sin;
        float const yNew = translated.x * sin + translated.y * cos;

        rotatedVertices.emplace_back(xNew + center.x, yNew + center.y);
    }

    return rotatedVertices;
}