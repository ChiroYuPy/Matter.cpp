//
// Created by adrian on 25/02/25.
//

#pragma once

#include <cmath>

struct Vector2 {
    float x, y;

    Vector2();

    Vector2(float x, float y);

    Vector2 operator+(const Vector2 &other) const;

    Vector2 operator-(const Vector2 &other) const;

    Vector2 operator-() const;

    Vector2 operator*(float scalar) const;

    Vector2 operator/(float scalar) const;

    Vector2 &operator+=(const Vector2 &other);

    Vector2 &operator-=(const Vector2 &other);

    Vector2 &operator*=(float scalar);

    Vector2 &operator/=(float scalar);

    float Magnitude() const;

    Vector2 Normalize() const;

    float Dot(const Vector2 &other) const;

    float Length() const;

    float LengthSquared() const;

    static float Distance(const Vector2 &a, const Vector2 &b);

    static Vector2 Lerp(const Vector2 &a, const Vector2 &b, float t);
};
