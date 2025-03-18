#include "Physics/Objects/RigidBody.h"

RigidBody::RigidBody(const Vector2f position, const float mass, const float friction)
    : Particle(position, mass), friction(friction) {
}

void RigidBody::Update(const float dt) {
    // Applique la friction à la vitesse du corps rigide
    velocity *= (1.0f - friction); // Modifie la vitesse pour simuler la friction

    // Met à jour la position de la particule (via la classe de base `Particle`)
    Particle::Update(dt); // Mise à jour de la position avec la vitesse actuelle
}

void RigidBody::SetFriction(const float newFriction) {
    friction = newFriction; // Modifier la friction
}

float RigidBody::GetFriction() const {
    return friction; // Retourne la valeur de la friction
}
