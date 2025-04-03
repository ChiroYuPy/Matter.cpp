//
// Created by adrian on 02/04/25.
//

#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "MATTER/math/Vector2.h"

struct CollisionInfo {
    bool collided;
    Vector2f normal;
    float depth;
    std::vector<Vector2f> contacts;

    explicit CollisionInfo(const bool collided = false, const Vector2f& normal = {}, const float depth = 0.0f)
        : collided(collided), normal(normal), depth(depth) {}

    void addContact(const Vector2f& contact) {
        contacts.push_back(contact);
    }
};

#endif //COLLISIONINFO_H
