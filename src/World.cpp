//
// Created by adrian on 07/02/25.
//

#include "../header/World.h"
#include <cstdlib>
#include <cmath>

bool randomBool(int percentage) {
    return (std::rand() % 100) < percentage;
}

World::World(sf::RenderWindow &window) : window(window), bounds(0, 0, static_cast<float>(window.getSize().x), static_cast<float>(window.getSize().y)) {

    const int rows = 8;
    const int cols = 20;
    const float spacing = 64.f;
    const sf::Vector2f startPos(50.f, 50.f);

    particles.reserve(rows * cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            float x = startPos.x + col * spacing;
            float y = startPos.y + row * spacing;

            int radius = 16;
            bool inert = false;

            particles.emplace_back(x, y, radius, /*mass*/ radius, inert);
        }
    }

    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            int idx = row * cols + col;

            if (col < cols - 1) {
                int rightIdx = row * cols + (col + 1);
                constraints.emplace_back(
                    particles[idx],
                    particles[rightIdx],
                    /*longueur repos*/ spacing,
                    /*raideur*/ 128.f,
                    /*amortissement*/ 0.5f
                );
            }

            // Contraintes verticales
            if (row < rows - 1) {
                int downIdx = (row + 1) * cols + col;
                constraints.emplace_back(
                    particles[idx],
                    particles[downIdx],
                    /*longueur repos*/ spacing,
                    /*raideur*/ 128.f,
                    /*amortissement*/ 0.5f
                );
            }

            // ➜ Diagonale vers la droite (row+1, col+1)
            if (row < rows - 1 && col < cols - 1) {
                int diagRightIdx = (row + 1) * cols + (col + 1);
                constraints.emplace_back(
                    particles[idx],
                    particles[diagRightIdx],
                    /*longueur repos*/ spacing * std::sqrt(2.f), // diagonal => √2 * spacing
                    /*raideur*/ 128.f,
                    /*amortissement*/ 0.5f
                );
            }

            // ➜ Diagonale vers la gauche (row+1, col-1)
            if (row < rows - 1 && col > 0) {
                int diagLeftIdx = (row + 1) * cols + (col - 1);
                constraints.emplace_back(
                    particles[idx],
                    particles[diagLeftIdx],
                    /*longueur repos*/ spacing * std::sqrt(2.f), // diagonal => √2 * spacing
                    /*raideur*/ 128.f,
                    /*amortissement*/ 0.5f
                );
            }
        }
    }
}

std::vector<Particle> World::getParticles() {
    return particles;
}

std::vector<Constraint> World::getConstraints() {
    return constraints;
}

void World::update(float dt) {
    for (auto &p: particles) {
        p.applyForce({0, 128.f});
        p.update(dt);
        p.handleWallCollisions(window);
    }

    for (auto &p: constraints) {
        p.update(dt);
    }
    checkCollisions();
}

void World::checkCollisions() {
    quadtree.clear();

    for (auto& p : particles) {
        quadtree.insert(&p);
    }

    for (auto& p : particles) {
        std::vector<Particle*> possibleCollisions;
        quadtree.retrieve(possibleCollisions, &p);

        for (const auto& other : possibleCollisions) {
            if (p == *other) continue;
            float depth;
            if (sf::Vector2f norm; intersectCircles(p, *other, norm, depth)) {
                separateParticles(p, *other, norm * depth);
                resolveCollisions(p, *other, norm);
            }
        }
    }
}

void World::separateParticles(Particle &p1, Particle &p2, sf::Vector2f normalDotDepth) {
    if (p2.isInert()) {
        p1.setPosition(p1.getPosition() - normalDotDepth);
    } else if (p1.isInert()) {
        p2.setPosition(p2.getPosition() + normalDotDepth);
    } else {
        p1.setPosition(p1.getPosition() - normalDotDepth / 2.f);
        p2.setPosition(p2.getPosition() + normalDotDepth / 2.f);
    }
}

float dotProduct(const sf::Vector2f &a, const sf::Vector2f &b) {
    return (a.x * b.x) + (a.y * b.y);
}

void World::resolveCollisions(Particle &p1, Particle &p2, sf::Vector2f normal) {
    sf::Vector2 relative_velocity = p2.getVelocity() - p1.getVelocity();

    if (dotProduct(relative_velocity, normal) > 0.0) return;
    float j = -2.0 * dotProduct(relative_velocity, normal) / 2.f;

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
