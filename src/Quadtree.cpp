//
// Created by adrian on 14/02/25.
//

#include "../header/Quadtree.h"

Quadtree::Quadtree(int level, sf::FloatRect bounds)
    : level(level), bounds(bounds) {
    for (int i = 0; i < 4; ++i)
        children[i] = nullptr;
}

Quadtree::~Quadtree() {
    clear();
}

void Quadtree::clear() {
    objects.clear();

    for (int i = 0; i < 4; ++i) {
        if (children[i]) {
            delete children[i];
            children[i] = nullptr;
        }
    }
}

void Quadtree::subdivide() {
    float halfWidth = bounds.width / 2.f;
    float halfHeight = bounds.height / 2.f;
    float x = bounds.left;
    float y = bounds.top;

    children[0] = new Quadtree(level + 1, sf::FloatRect(x, y, halfWidth, halfHeight)); // Nord-Ouest
    children[1] = new Quadtree(level + 1, sf::FloatRect(x + halfWidth, y, halfWidth, halfHeight)); // Nord-Est
    children[2] = new Quadtree(level + 1, sf::FloatRect(x, y + halfHeight, halfWidth, halfHeight)); // Sud-Ouest
    children[3] = new Quadtree(level + 1, sf::FloatRect(x + halfWidth, y + halfHeight, halfWidth, halfHeight)); // Sud-Est
}

int Quadtree::getIndex(Particle* p) {
    float verticalMidpoint = bounds.left + bounds.width / 2.f;
    float horizontalMidpoint = bounds.top + bounds.height / 2.f;

    bool topQuadrant = (p->getPosition().y < horizontalMidpoint);
    bool bottomQuadrant = !topQuadrant;
    bool leftQuadrant = (p->getPosition().x < verticalMidpoint);
    bool rightQuadrant = !leftQuadrant;

    if (topQuadrant && leftQuadrant) return 0; // Nord-Ouest
    if (topQuadrant && rightQuadrant) return 1; // Nord-Est
    if (bottomQuadrant && leftQuadrant) return 2; // Sud-Ouest
    if (bottomQuadrant && rightQuadrant) return 3; // Sud-Est

    return -1; // L'objet est sur la frontière
}

void Quadtree::insert(Particle* p) {
    if (children[0]) {
        int index = getIndex(p);
        if (index != -1) {
            children[index]->insert(p);
            return;
        }
    }

    objects.push_back(p);

    if (objects.size() > MAX_OBJECTS && level < MAX_LEVELS) {
        if (!children[0]) {
            subdivide();
        }

        auto it = objects.begin();
        while (it != objects.end()) {
            int index = getIndex(*it);
            if (index != -1) {
                children[index]->insert(*it);
                it = objects.erase(it);
            } else {
                ++it;
            }
        }
    }
}

void Quadtree::retrieve(std::vector<Particle*>& returnObjects, Particle* p) {
    int index = getIndex(p);
    if (index != -1 && children[0]) {
        children[index]->retrieve(returnObjects, p);
    }

    returnObjects.insert(returnObjects.end(), objects.begin(), objects.end());
}