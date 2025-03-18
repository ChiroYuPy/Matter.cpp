//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Particle.h"

Particle::Particle(Vector2 position, float mass)
    : position(position), velocity(0, 0), acceleration(0, 0), mass(mass), active(true), inert(false) {
}

void Particle::ApplyForce(const Vector2 &force) {
    acceleration += force / mass;
}

void Particle::ApplyAcceleration(const Vector2 &force) {
    acceleration += force;
}

void Particle::Update(float dt) {
    if (inert) {
        velocity *= 0;
        return;
    }

    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = Vector2(0, 0);
}
