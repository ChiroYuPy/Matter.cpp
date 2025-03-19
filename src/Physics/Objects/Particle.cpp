//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Particle.h"

Particle::Particle(const Vector2f position, const float mass)
    : position(position), velocity(0, 0), acceleration(0, 0), mass(mass), active(true), inert(false) {
}

void Particle::applyForce(const Vector2f &force) {
    acceleration += force / mass;
}

void Particle::applyAcceleration(const Vector2f &force) {
    acceleration += force;
}

void Particle::update(const float dt) {
    if (inert) {
        velocity *= 0;
        return;
    }

    velocity += acceleration * dt;
    position += velocity * dt;
    acceleration = Vector2f(0, 0);
}

void Particle::setVelocity(const Vector2f newPosition) { velocity = newPosition; }
