//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Vector2.h"

struct AABB {
    Vector2 min;
    Vector2 max;

    AABB(Vector2 min, Vector2 max);

    bool Intersect(const AABB& other) const;
    bool Contain(const Vector2& point) const;

    Vector2 GetCenter() const;
    Vector2 GetSize() const;
    Vector2 GetMin() const;
    Vector2 GetMax() const;

    float GetWidth() const;
    float GetHeight() const;
};
