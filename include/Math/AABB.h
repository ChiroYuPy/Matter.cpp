//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Vector2.h"

struct AABB {
    Vector2f min;
    Vector2f max;

    AABB(Vector2f min, Vector2f max);

    [[nodiscard]] bool intersect(const AABB &other) const;

    [[nodiscard]] bool contain(const Vector2f &point) const;

    [[nodiscard]] Vector2f getCenter() const;

    [[nodiscard]] Vector2f getSize() const;

    [[nodiscard]] Vector2f getMin() const;

    [[nodiscard]] Vector2f getMax() const;

    [[nodiscard]] float getWidth() const;

    [[nodiscard]] float getHeight() const;
};
