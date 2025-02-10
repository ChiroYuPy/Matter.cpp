//
// Created by adrian on 07/02/25.
//

#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include "Particle.h"

class World {
public:
    World(sf::RenderWindow& window);
    void update(float dt);
    void draw();

private:
    std::vector<Particle> particles;
    sf::RenderWindow& window;
    void checkCollisions();

    void resolveCollisions(Particle &p1, Particle &p2, sf::Vector2f normal);

    static bool intersectCircles(Particle &p1, Particle &p2, sf::Vector2f &norm, float &depth);
    void separateParticles(Particle& p1, Particle& p2, sf::Vector2f normalDotDepth);
};

#endif // WORLD_H
