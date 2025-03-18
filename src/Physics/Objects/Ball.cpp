//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Ball.h"

Ball::Ball(Vector2 position, float radius, float mass, float friction)
    : RigidBody(position, mass, friction), radius(radius) {}

void Ball::Update(float dt) {
    RigidBody::Update(dt);
}

AABB Ball::GetAABB() const {
    Vector2 min = position - Vector2(radius, radius);
    Vector2 max = position + Vector2(radius, radius);
    return AABB(min, max);
}

float Ball::GetRadius() const {
  return radius;
}