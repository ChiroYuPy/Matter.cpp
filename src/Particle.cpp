//
// Created by adrian on 07/02/25.
//

#include "../header/Particle.h"
#include <cmath>

Particle::Particle(float x, float y, float radius, bool inert)
    : position(x, y), radius(radius), inert(inert) {
    shape.setRadius(radius);
    shape.setOrigin(radius, radius);
    shape.setPosition(position);
    shape.setFillColor(sf::Color::White);
}

void Particle::applyForce(const sf::Vector2f& force) {
    acceleration += force;
}

void Particle::update(float dt) {
    if (inert) return;
    velocity += acceleration * dt;
    position += velocity * dt;
    shape.setPosition(position);
    acceleration = {0.f, 0.f}; // Reset acceleration after applying forces
}

void Particle::handleWallCollisions(const sf::RenderWindow& window) {
    if (position.x - radius < 0) {
        position.x = radius;
        velocity.x = 0; // Stop movement instead of bouncing
    } else if (position.x + radius > window.getSize().x) {
        position.x = window.getSize().x - radius;
        velocity.x = 0;
    }
    if (position.y - radius < 0) {
        position.y = radius;
        velocity.y = 0;
    } else if (position.y + radius > window.getSize().y) {
        position.y = window.getSize().y - radius;
        velocity.y = 0;
    }
}

void Particle::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::Vector2f Particle::getPosition() const {
    return position;
}

void Particle::setPosition(const sf::Vector2f& pos) {
    position = pos;
    shape.setPosition(position);
}

sf::Vector2f Particle::getVelocity() const {
    return velocity;
}

void Particle::setVelocity(const sf::Vector2f& vel) {
    velocity = vel;
}

float Particle::getRadius() const {
    return radius;
}

float Particle::getMass() const {
    return mass;
}

float Particle::getAngle() const {
    return angle;
}

void Particle::setInert(const bool ine) {
    inert = ine;
}

bool Particle::isInert() const {
    return inert;
}