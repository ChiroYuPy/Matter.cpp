//
// Created by adrian on 07/02/25.
//

#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Quadtree.h"

#include "Particle.h"
#include "Constraint.h"

class World {
public:
    World(sf::RenderWindow &window);

    void createRandomParticles(int count);

    void update(float dt);

    void createGrid(int rows, int cols, float spacing, sf::Vector2f startPos);

    void createGridConstraints(int rows, int cols, float spacing);

    void createCirclePattern(int count, float radius, sf::Vector2f center);

    void addConstraint(int idx1, int idx2, float length);

    std::vector<Particle>& getParticles();

    std::vector<Constraint>& getConstraints();

private:
    sf::FloatRect bounds;
    Quadtree quadtree = Quadtree(4, bounds);

    std::vector<Particle> particles;
    std::vector<Constraint> constraints;

    sf::RenderWindow &window;

    void checkCollisions();

    void resolveCollisions(Particle &p1, Particle &p2, sf::Vector2f normal);

    static bool intersectCircles(Particle &p1, Particle &p2, sf::Vector2f &norm, float &depth);

    void separateParticles(Particle &p1, Particle &p2, sf::Vector2f normalDotDepth);
};

#endif // WORLD_H
