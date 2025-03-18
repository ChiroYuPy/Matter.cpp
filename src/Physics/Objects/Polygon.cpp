//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Polygon.h"

Polygon::Polygon(const Vector2& position, float mass, float friction, const std::vector<Vector2>& verts)
    : RigidBody(position, mass, friction), vertices(verts) {}

void Polygon::Update(float dt) {
    RigidBody::Update(dt);
}

AABB Polygon::GetAABB() const {
    if (vertices.empty()) return AABB(Vector2(0, 0), Vector2(0, 0));

    Vector2 min = vertices[0];
    Vector2 max = vertices[0];

    for (const auto& v : vertices) {
        min.x = std::min(min.x, v.x);
        min.y = std::min(min.y, v.y);
        max.x = std::max(max.x, v.x);
        max.y = std::max(max.y, v.y);
    }

    return AABB(min, max);
}

const std::vector<Vector2>& Polygon::GetVertices() const {
    return vertices;
}
