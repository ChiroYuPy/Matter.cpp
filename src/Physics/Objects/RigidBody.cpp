#include "Physics/Objects/RigidBody.h"

RigidBody::RigidBody(const Vector2f position, const float mass, const float friction)
    : Particle(position, mass), friction(friction), angle(0) {
}

void RigidBody::SetFriction(const float newFriction) {
    friction = newFriction;
}

float RigidBody::getFriction() const {
    return friction;
}

void RigidBody::setAngle(const float newAngle) {
    angle = newAngle;
}

float RigidBody::getAngle() const {
    return angle;
}