//
// Created by adrian on 02/04/25.
//

#ifndef COLLISIONINFO_H
#define COLLISIONINFO_H

#include "MATTER/math/Vector2.h"

struct CollisionInfo {
    std::vector<Vector2f> contacts;
    bool collided;
    Vector2f normal;
    float depth;

    explicit CollisionInfo(const bool collided = false,
                           const Vector2f& normal = {},
                           const float depth = 0.0f,
                           const std::vector<Vector2f>& contacts = {}
    ) : contacts(contacts), collided(collided), normal(normal), depth(depth) {}
};

#endif //COLLISIONINFO_H
