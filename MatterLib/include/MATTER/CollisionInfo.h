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

    CollisionInfo(const bool collided, const Vector2f normal, const float depth) :
    collided(collided), normal(normal), depth(depth) {}
};

#endif //COLLISIONINFO_H
