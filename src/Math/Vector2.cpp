//
// Created by adrian on 25/02/25.
//

#include "Math/Vector2.h"

template<typename T>
Vector2<T>::Vector2() : x(0), y(0) {
}

template<typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2 &other) const {
    return Vector2(x + other.x, y + other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2 &other) const {
    return Vector2(x - other.x, y - other.y);
}

template<typename T>
Vector2<T> Vector2<T>::operator-() const {
    return Vector2(-x, -y);
}

template<typename T>
Vector2<T> Vector2<T>::operator*(T scalar) const {
    return Vector2(x * scalar, y * scalar);
}

template<typename T>
Vector2<T> Vector2<T>::operator/(const T scalar) const {
    return (scalar != 0) ? Vector2(x / scalar, y / scalar) : Vector2();
}

template<typename T>
Vector2<T>& Vector2<T>::operator+=(const Vector2 &other) {
    x += other.x;
    y += other.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator-=(const Vector2 &other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator*=(const T scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

template<typename T>
Vector2<T>& Vector2<T>::operator/=(const T scalar) {
    if (scalar != 0) {
        x /= scalar;
        y /= scalar;
    }
    return *this;
}

template<typename T>
T Vector2<T>::Magnitude(const Vector2 &a) {
    return std::sqrt(a.x * a.x + a.y * a.y);
}

template<typename T>
T Vector2<T>::Length(const Vector2 &a) {
    return Magnitude(a);
}

template<typename T>
T Vector2<T>::LengthSquared(const Vector2 &a) {
    return a.x * a.x + a.y * a.y;
}

template<typename T>
T Vector2<T>::Dot(const Vector2 &a, const Vector2 &b) {
    return a.x * b.x + a.y * b.y;
}

template<typename T>
T Vector2<T>::Distance(const Vector2 &a, const Vector2 &b) {
    return Magnitude(b - a);
}

template<typename T>
Vector2<T> Vector2<T>::Normalize(const Vector2 &a) {
    const float mag = Magnitude(a);
    return (mag != 0) ? (a / mag) : Vector2(0, 0);
}

template<typename T>
Vector2<T> Vector2<T>::Lerp(const Vector2 &a, const Vector2 &b, const T t) {
    return a + (b - a) * t;
}

template class Vector2<int>;
template class Vector2<float>;
template class Vector2<double>;
