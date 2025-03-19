#include "Physics/Objects/RigidBody.h"

RigidBody::RigidBody(const Vector2f position)
    : Particle(position), restitution(0), friction(0), angle(0) {
}

void RigidBody::setRestitution(const float newRestitution) {
    restitution = newRestitution;
}

float RigidBody::getRestitution() const {
    return restitution;
}

void RigidBody::setFriction(const float newFriction) {
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