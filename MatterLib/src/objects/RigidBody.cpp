#include "MATTER/objects/RigidBody.h"
#include "MATTER/math/Constant.h"

RigidBody::RigidBody(const Vector2f position)
: Particle(position), restitution(0), friction(0), angle(0),
angularVelocity(1), inertia(1), invertedInertia(1) {
}

void RigidBody::setRestitution(const float newRestitution) { restitution = newRestitution; }
float RigidBody::getRestitution() const { return restitution; }

void RigidBody::setFriction(const float newFriction) { friction = newFriction; }
float RigidBody::getFriction() const { return friction; }

void RigidBody::setAngle(const float newAngle) { angle = newAngle; }
float RigidBody::getAngle() const { return angle; }

void RigidBody::setAngularVelocity(const float newAngularVelocity) { angularVelocity = newAngularVelocity; }
float RigidBody::getAngularVelocity() const { return angularVelocity; }

void RigidBody::setInertia(const float newInertia) {
    inertia = newInertia;
    if (inertia > 0) invertedInertia = 1 / inertia;
    else invertedInertia = std::numeric_limits<float>::infinity();
}

float RigidBody::getInertia() const {
    return inertia;
}

float RigidBody::getInvertedInertia() const {
    return invertedInertia;
}

float RigidBody::calculateInertia() const {
    return mass;
}
