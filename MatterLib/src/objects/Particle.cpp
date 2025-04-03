//
// Created by adrian on 25/02/25.
//

#include "MATTER/objects/Particle.h"

Particle::Particle(const Vector2f position)
    : position(position), velocity(0, 0), acceleration(0, 0), inert(false), active(true), mass(1), invertedMass(1) {
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

[[nodiscard]] float Particle::getMass() const { if (isInert()) { return std::numeric_limits<float>::infinity(); } return mass; }

void Particle::setMass(const float newMass) {
    mass = newMass;
    if (mass > 0) invertedMass = 1 / mass;
    else invertedMass = std::numeric_limits<float>::infinity();
}
