//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Polygon.h"

Polygon::Polygon(const Vector2f& position, const float mass, const float friction, const std::vector<Vector2f>& verts)
    : RigidBody(position, mass, friction), vertices(verts) {}

void Polygon::Update(const float dt) {
    RigidBody::Update(dt);
}

AABB Polygon::GetAABB() const {
    if (vertices.empty()) return {Vector2f(), Vector2f()};

    Vector2 min = vertices[0];
    Vector2 max = vertices[0];

    for (const auto& v : vertices) {
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
    }

    return {min, max};
}

const std::vector<Vector2f>& Polygon::GetVertices() const {
    return vertices;
}
