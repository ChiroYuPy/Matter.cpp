//
// Created by adrian on 25/02/25.
//

#ifndef SOLVER_H
#define SOLVER_H

#include "Objects/RigidBody.h"
#include "Collisioner.h"

class Solver {
public:
    static void ResolveCollision(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision);
    static void ApplyImpulse(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision);
    static void ApplySeparation(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision);
};

#endif // SOLVER_H
