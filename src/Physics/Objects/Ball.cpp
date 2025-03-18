//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Ball.h"

Ball::Ball(const Vector2f position, const float radius, const float mass, const float friction)
    : RigidBody(position, mass, friction), radius(radius) {
}

void Ball::Update(const float dt) {
    RigidBody::Update(dt);
}

AABB Ball::GetAABB() const {
    const Vector2 min = position - Vector2(radius, radius);
    const Vector2 max = position + Vector2(radius, radius);
    return {min, max};
}

float Ball::GetRadius() const {
    return radius;
}
