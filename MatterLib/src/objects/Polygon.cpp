//
// Created by adrian on 26/02/25.
//

#include "MATTER/objects/Polygon.h"

Polygon::Polygon(const Vector2f &position, const std::vector<Vector2f> &verts)
    : RigidBody(position), vertices(verts) {
}

void Polygon::update(float dt) {
    RigidBody::update(dt);
}

AABB Polygon::getAABB() const {
    auto transformedVertices = getVertices();
    if (transformedVertices.empty()) return {Vector2f(), Vector2f()};

    Vector2f min = transformedVertices[0];
    Vector2f max = transformedVertices[0];

    for (const auto &v : transformedVertices) {
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
    }

    return {min, max};
}

std::vector<Vector2f> Polygon::getVertices() const {
    std::vector<Vector2f> transformedVertices;
    transformedVertices.reserve(vertices.size());

    const Vector2f position = getPosition();
    const float cosA = std::cos(angle);
    const float sinA = std::sin(angle);

    for (const auto &v : vertices) {
        const float xNew = v.x * cosA - v.y * sinA;
        const float yNew = v.x * sinA + v.y * cosA;
        transformedVertices.emplace_back(xNew + position.x, yNew + position.y);
    }

    return transformedVertices;
}
