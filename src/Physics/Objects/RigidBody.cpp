#include "Physics/Objects/RigidBody.h"

RigidBody::RigidBody(const Vector2f position, const float mass, const float friction)
    : Particle(position, mass), friction(friction) {
}

void RigidBody::SetFriction(const float newFriction) {
    friction = newFriction; // Modifier la friction
}

float RigidBody::getFriction() const {
    return friction; // Retourne la valeur de la friction
}
