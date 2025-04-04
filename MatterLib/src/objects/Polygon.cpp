//
// Created by adrian on 26/02/25.
//

#include <numbers>

#include "MATTER/objects/Polygon.h"

#include "MATTER/math/Constant.h"

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
    const float radians = angle * (PI / 180.0f);
    const float cosA = std::cos(radians);
    const float sinA = std::sin(radians);

    for (const auto &v : vertices) {
        const float xNew = v.x * cosA - v.y * sinA;
        const float yNew = v.x * sinA + v.y * cosA;
        transformedVertices.emplace_back(xNew + position.x, yNew + position.y);
    }

    return transformedVertices;
}

[[nodiscard]] float Polygon::calculateInertia() const {
    float inertia = 0.0f;
    float area = 0.0f;

    const size_t numVertices = vertices.size();

    for (size_t i = 0; i < numVertices; i++) {
        const size_t next = (i + 1) % numVertices;

        const float xi = vertices[i].x;
        const float yi = vertices[i].y;
        const float xi1 = vertices[next].x;
        const float yi1 = vertices[next].y;

        const float crossProduct = xi * yi1 - xi1 * yi;

        area += crossProduct;

        inertia += (xi * xi + yi * yi + xi * xi1 + yi * yi1 + xi1 * xi1 + yi1 * yi1) * crossProduct;
    }

    area *= 0.5f;

    if (area == 0) return 0.0f;

    inertia /= (6.0f * area);

    inertia *= mass;

    return inertia;
}
