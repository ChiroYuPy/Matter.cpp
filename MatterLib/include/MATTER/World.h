//
// Created by adrian on 25/02/25.
//

#pragma once

#include <vector>

#ifndef WORLD_H
#define WORLD_H

#include "MATTER/objects/Particle.h"
#include "MATTER/objects/RigidBody.h"
#include "MATTER/objects/Join.h"
#include "MATTER/Collisioner.h"
#include "MATTER/Solver.h"

struct CollisionPair {
    RigidBody *bodyA;
    RigidBody *bodyB;

    CollisionPair(RigidBody *bodyA, RigidBody *bodyB) : bodyA(bodyA), bodyB(bodyB) {}
};

class World {
public:
    World() = default;

    void addParticle(Particle *particle);

    void addRigidBody(RigidBody *body);

    void addJoin(Join *join);

    void update(float dt);

    void clear();

    void setUpdatePerSeconds(int newUpdatePerSeconds);

    void setMaxUpdatePerFrame(int newMaxUpdatePerFrame);

    void setGravity(Vector2f newGravity);

    [[nodiscard]] const std::vector<Particle *>& GetParticles() const;

    [[nodiscard]] const std::vector<RigidBody *>& GetRigidBodies() const;

    [[nodiscard]] const std::vector<Join *>& GetJoins() const;

private:
    void stepObjects(float dt);

    void stepJoins(float dt) const;

    void applyGravity() const;

    void applyAirFriction() const;

    void detectCollisions();

    void broadPhase();

    void narrowPhase();

    void resolveCollisions(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision);

    int updatePerSeconds = 60;
    int maxUpdatePerFrame = 1;

    Vector2f gravity;

    std::vector<CollisionPair> collisionPairs;

    std::vector<Particle *> particles;
    std::vector<RigidBody *> rigidBodies;
    std::vector<Join *> joins;
};

#endif // WORLD_H