//
// Created by adrian on 25/02/25.
//

#include "Physics/Objects/Particle.h"

Particle::Particle(const Vector2f position, const float mass)
    : position(position), velocity(0, 0), acceleration(0, 0), inert(false), active(true), mass(mass) {
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

[[nodiscard]] Vector2f Particle::getPosition() const { return position; }
void Particle::setPosition(const Vector2f newPosition) { position = newPosition; }

[[nodiscard]] Vector2f Particle::getVelocity() const { return velocity; }
void Particle::setVelocity(const Vector2f newPosition) { velocity = newPosition; }

[[nodiscard]] bool Particle::isInert() const { return inert; }
void Particle::setInert(const bool newInert) { inert = newInert; }

[[nodiscard]] bool Particle::isActive() const { return active; }
void Particle::setActive(const bool newActive) { active = newActive; }

[[nodiscard]] float Particle::getMass() const { return mass; }
void Particle::setMass(const float newMass) { mass = newMass; }