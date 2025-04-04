//
// Created by adrian on 25/02/25.
//

#pragma once

#include <cmath>
#include <iostream>

#ifndef VECTOR2_H
#define VECTOR2_H

template<typename T>
struct Vector2 {
    T x, y;

	Vector2();
    Vector2(T x, T y);

    Vector2 operator+(const Vector2 &other) const;
    Vector2 operator-(const Vector2 &other) const;
    Vector2 operator-() const;
    Vector2 operator*(T scalar) const;
    Vector2 operator/(T scalar) const;
    Vector2 &operator+=(const Vector2 &other);
    Vector2 &operator-=(const Vector2 &other);
    Vector2 &operator*=(T scalar);
    Vector2 &operator/=(T scalar);

    static T Magnitude(const Vector2 &a);
    static T Dot(const Vector2 &a, const Vector2 &b);
    static T Length(const Vector2 &a);
    static T LengthSquared(const Vector2 &a);
    static T Distance(const Vector2 &a, const Vector2 &b);
    static Vector2 Normalize(const Vector2 &a);
    static float Cross(const Vector2 &a, const Vector2 &b);
    static Vector2 Lerp(const Vector2 &a, const Vector2 &b, T t);
};

// Vector2 aliases

extern template struct Vector2<int>;
extern template struct Vector2<float>;
extern template struct Vector2<double>;

using Vector2i = Vector2<int>;
using Vector2f = Vector2<float>;
using Vector2d = Vector2<double>;

#endif // VECTOR2_H