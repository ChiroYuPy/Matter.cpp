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

    void update(float dt);

    std::vector<Particle> getParticles();

    std::vector<Constraint> getConstraints();

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
