//
// Created by adrian on 25/02/25.
//

#include "MATTER/math/AABB.h"

AABB::AABB(const Vector2f min, const Vector2f max) : min(min), max(max) {
}

bool AABB::intersect(const AABB &other) const {
    return (min.x < other.max.x && max.x > other.min.x &&
            min.y < other.max.y && max.y > other.min.y);
}

bool AABB::contain(const Vector2f &point) const {
    return (point.x >= min.x && point.x <= max.x &&
            point.y >= min.y && point.y <= max.y);
}

Vector2f AABB::getCenter() const {
    return {(min.x + max.x) / 2.0f, (min.y + max.y) / 2.0f};
}

Vector2f AABB::getSize() const {
    return {max.x - min.x, max.y - min.y};
}

Vector2f AABB::getMin() const {
    return min;
}

Vector2f AABB::getMax() const {
    return max;
}

float AABB::getWidth() const {
    return max.x - min.x;
}

float AABB::getHeight() const {
    return max.y - min.y;
}
