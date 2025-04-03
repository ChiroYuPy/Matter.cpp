//
// Created by adrian on 02/04/25.
//

#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "MATTER/math/Vector2.h"

struct CollisionInfo {
private:
    std::vector<Vector2f> contacts;

public:
    bool collided;
    Vector2f normal;
    float depth;

    explicit CollisionInfo(const bool collided = false, const Vector2f& normal = {}, const float depth = 0.0f)
        : collided(collided), normal(normal), depth(depth) {}

    void addContact(const Vector2f& contact) {
        if (contacts.size() < 2) contacts.push_back(contact);
        else std::cerr << "A CollisionInfo can have only 2 contact points maximum !" << std::endl;
    }

    std::vector<Vector2f>& getContactPoints() {
        return contacts;
    }
};

#endif //COLLISIONINFO_H
