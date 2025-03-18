//
// Created by adrian on 25/02/25.
//

#include "Math/AABB.h"

AABB::AABB(Vector2 min, Vector2 max) : min(min), max(max) {}

bool AABB::Intersect(const AABB& other) const {
    return (min.x < other.max.x && max.x > other.min.x &&
            min.y < other.max.y && max.y > other.min.y);
}

bool AABB::Contain(const Vector2& point) const {
    return (point.x >= min.x && point.x <= max.x &&
            point.y >= min.y && point.y <= max.y);
}

Vector2 AABB::GetCenter() const {
    return Vector2((min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f);
}

Vector2 AABB::GetSize() const {
    return Vector2(max.x - min.x, max.y - min.y);
}

Vector2 AABB::GetMin() const {
    return min;
}

Vector2 AABB::GetMax() const {
    return max;
}

float AABB::GetWidth() const {
    return max.x - min.x;
}

float AABB::GetHeight() const {
    return max.y - min.y;
}