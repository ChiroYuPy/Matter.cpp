#include "../header/World.h"
#include <cstdlib>
#include <cmath>
#include <iostream>

bool randomBool(int percentage) {
    return (std::rand() % 100) < percentage;
}

float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b) {
    return (a.x * b.x) + (a.y * b.y);
}

World::World(sf::RenderWindow &window) : window(window), bounds(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)) {
    //createRandomParticles(3000);
    createGrid(24, 24, 32.f, {50.f, 50.f});
    //createGrid(3, 3, 64.f, {800.f, 50.f});
}

void World::createRandomParticles(int count) {
    particles.reserve(particles.size() + count);
    for (int i = 0; i < count; i++) {
        float x = static_cast<float>(std::rand() % window.getSize().x);
        float y = static_cast<float>(std::rand() % window.getSize().y);
        int radius = 4;
        bool inert = randomBool(50);
        particles.emplace_back(x, y, radius, radius, inert);
    }
}

void World::createGrid(int rows, int cols, float spacing, sf::Vector2f startPos) {
    int size = particles.size();
    particles.reserve(size + rows * cols);

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startPos.x + col * spacing;
            float y = startPos.y + row * spacing;
            particles.emplace_back(x, y, 16, 16, false);  // Ajouter directement à 'particles'
        }
    }

    constraints.reserve(constraints.size() + (rows * cols * 4));

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int idx = row * cols + col;

            if (col < cols - 1) {
                int rightIdx = row * cols + (col + 1);
                constraints.emplace_back(particles[size + idx], particles[size + rightIdx], spacing, 128.f, 0.5f);
            }

            if (row < rows - 1) {
                int bottomIdx = (row + 1) * cols + col;
                constraints.emplace_back(particles[size + idx], particles[size + bottomIdx], spacing, 128.f, 0.5f);
            }

            if (row < rows - 1 && col < cols - 1) {
                int bottomRightIdx = (row + 1) * cols + (col + 1);
                constraints.emplace_back(particles[size + idx], particles[size + bottomRightIdx], spacing * std::sqrt(2.f), 128.f, 0.5f);
            }

            if (row < rows - 1 && col > 0) {
                int bottomLeftIdx = (row + 1) * cols + (col - 1);
                constraints.emplace_back(particles[size + idx], particles[size + bottomLeftIdx], spacing * std::sqrt(2.f), 128.f, 0.5f);
            }
        }
    }
}

std::vector<Particle>& World::getParticles() { return particles; }
std::vector<Constraint>& World::getConstraints() { return constraints; }

void World::update(float dt) {
    for (auto &p : particles) {
        p.applyForce({0, 128.f});
        p.update(dt);
        p.handleWallCollisions(window);
    }
    for (auto &c : constraints) c.update(dt);
    checkCollisions();
}

void World::checkCollisions() {
    quadtree.clear();
    for (auto &p : particles) quadtree.insert(&p);
    for (auto &p : particles) {
        std::vector<Particle*> possibleCollisions;
        quadtree.retrieve(possibleCollisions, &p);
        for (auto *other : possibleCollisions) {
            if (p == *other) continue;
            sf::Vector2f norm; float depth;
            if (intersectCircles(p, *other, norm, depth)) {
                separateParticles(p, *other, norm * depth);
                resolveCollisions(p, *other, norm);
            }
        }
    }
}

void World::separateParticles(Particle &p1, Particle &p2, sf::Vector2f normalDotDepth) {
    if (p2.isInert()) p1.setPosition(p1.getPosition() - normalDotDepth);
    else if (p1.isInert()) p2.setPosition(p2.getPosition() + normalDotDepth);
    else {
        p1.setPosition(p1.getPosition() - normalDotDepth / 2.f);
        p2.setPosition(p2.getPosition() + normalDotDepth / 2.f);
    }
}

void World::resolveCollisions(Particle &p1, Particle &p2, sf::Vector2f normal) {
    sf::Vector2f relVelocity = p2.getVelocity() - p1.getVelocity();
    if (dotProduct(relVelocity, normal) > 0.0) return;
    float j = -2.0 * dotProduct(relVelocity, normal) / 2.f;
    sf::Vector2f impulse = j * normal;
    p1.setVelocity(p1.getVelocity() - impulse);
    p2.setVelocity(p2.getVelocity() + impulse);
}

bool World::intersectCircles(Particle &p1, Particle &p2, sf::Vector2f &norm, float &depth) {
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
