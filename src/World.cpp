//
// Created by adrian on 07/02/25.
//

#include "../header/World.h"
#include <cstdlib>
#include <cmath>

bool randomBool(int percentage) {
    return (std::rand() % 100) < percentage;
}

World::World(sf::RenderWindow& window) : window(window) {
    for (int i = 0; i < 512; ++i) {
        float x = static_cast<float>(rand() % window.getSize().x);
        float y = static_cast<float>(rand() % window.getSize().y);
        bool inert = randomBool(10);
        particles.emplace_back(x, y, 24.f, inert);
    }
}

void World::update(float dt) {
    for (auto& p : particles) {
        p.applyForce({-64.f, 64.f});
        p.update(dt);
        p.handleWallCollisions(window);
    }
    checkCollisions();
}

void World::draw() {
    for (const auto& p : particles)
        p.draw(window);
}

void World::checkCollisions() {
    for (size_t i = 0; i < particles.size(); ++i) {
        for (size_t j = i + 1; j < particles.size(); ++j) {
            sf::Vector2f norm;
            float depth;
            if (intersectCircles(particles[i], particles[j], norm, depth)) {
                separateParticles(particles[i], particles[j], norm * depth);
                resolveCollisions(particles[i], particles[j], norm);
            }
        }
    }
}

void World::separateParticles(Particle& p1, Particle& p2, sf::Vector2f normalDotDepth) {
    if (p2.isInert()) {
        p1.setPosition(p1.getPosition() - normalDotDepth);
    } else if (p1.isInert()) {
        p2.setPosition(p2.getPosition() + normalDotDepth);
    } else {
        p1.setPosition(p1.getPosition() - normalDotDepth / 2.f);
        p2.setPosition(p2.getPosition() + normalDotDepth / 2.f);
    }
}

float dotProduct(const sf::Vector2f& a, const sf::Vector2f& b) {
    return (a.x * b.x) + (a.y * b.y);
}

void World::resolveCollisions(Particle& p1, Particle& p2, sf::Vector2f normal) {
    sf::Vector2 relative_velocity = p2.getVelocity() - p1.getVelocity();

        if (dotProduct(relative_velocity, normal) > 0.0) return;
        float j = - 2.0 * dotProduct(relative_velocity, normal) / 2.f;

        sf::Vector2f impulse = j * normal;

        p1.setVelocity(p1.getVelocity() - impulse);
        p2.setVelocity(p2.getVelocity() + impulse);
}

bool World::intersectCircles(Particle& p1, Particle& p2, sf::Vector2f& norm, float& depth) {
    sf::Vector2f delta = p2.getPosition() - p1.getPosition();
    float distance = std::sqrt(delta.x * delta.x + delta.y * delta.y);
    float combinedRadius = p1.getRadius() + p2.getRadius();

    if (distance < combinedRadius) {
        norm = delta / distance;
        depth = combinedRadius - distance;
        return true;
    }
    return false;
}