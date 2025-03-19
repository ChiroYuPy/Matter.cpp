//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Ball.h"

Ball::Ball(const Vector2f position, const float radius)
    : RigidBody(position), radius(radius) {
}

void Ball::update(const float dt) {
    RigidBody::update(dt);
}

AABB Ball::getAABB() const {
    const Vector2 min = position - Vector2(radius, radius);
    const Vector2 max = position + Vector2(radius, radius);
    return {min, max};
}

float Ball::getRadius() const {
    return radius;
}

[[nodiscard]] BodyType Ball::getType() const {
    return BodyType::Ball;
}