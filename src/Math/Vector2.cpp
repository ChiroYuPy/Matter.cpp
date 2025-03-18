//
// Created by adrian on 25/02/25.
//

#include "Math/Vector2.h"

Vector2::Vector2() : x(0), y(0) {
}

Vector2::Vector2(float x, float y) : x(x), y(y) {
}

Vector2 Vector2::operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
}

Vector2 Vector2::operator-() const {
    return Vector2(-x, -y);
}

Vector2 Vector2::operator*(float scalar) const {
    return Vector2(x * scalar, y * scalar);
}

Vector2 Vector2::operator/(float scalar) const {
    return (scalar != 0) ? Vector2(x / scalar, y / scalar) : Vector2(0, 0);
}

Vector2 &Vector2::operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2 &Vector2::operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2 &Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2 &Vector2::operator/=(float scalar) {
    if (scalar != 0) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

float Vector2::Magnitude() const {
    return std::sqrt(x * x + y * y);
}

float Vector2::Length() const {
    return Magnitude();
}

float Vector2::LengthSquared() const {
    return x * x + y * y;
}

Vector2 Vector2::Normalize() const {
    float mag = Magnitude();
    return (mag != 0) ? (*this / mag) : Vector2(0, 0);
}

float Vector2::Dot(const Vector2 &other) const {
    return x * other.x + y * other.y;
}

float Vector2::Distance(const Vector2 &a, const Vector2 &b) {
    return (b - a).Magnitude();
}

Vector2 Vector2::Lerp(const Vector2 &a, const Vector2 &b, float t) {
    return a + (b - a) * t;
}
