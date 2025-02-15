//
// Created by adrian on 14/02/25.
//

#ifndef QUADTREE_H
#define QUADTREE_H


#include <vector>
#include <SFML/Graphics.hpp>
#include "Particle.h"

class Quadtree {
private:
    static constexpr int MAX_OBJECTS = 4;
    static constexpr int MAX_LEVELS = 6;

    int level;
    sf::FloatRect bounds;
    std::vector<Particle*> objects;
    Quadtree* children[4];

    void subdivide();
    int getIndex(Particle* p);

public:
    Quadtree(int level, sf::FloatRect bounds);
    ~Quadtree();

    void clear();
    void insert(Particle* p);
    void retrieve(std::vector<Particle*>& returnObjects, Particle* p);
};

#endif //QUADTREE_H
