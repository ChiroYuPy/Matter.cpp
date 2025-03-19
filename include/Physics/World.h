//
// Created by adrian on 25/02/25.
//

#pragma once
#include <vector>
#include "Objects/Particle.h"
#include "Objects/RigidBody.h"
#include "Objects/Join.h"
#include "Collisioner.h"

struct CollisionPair {
    RigidBody *bodyA;
    RigidBody *bodyB;
};

class World {
public:
    World() = default;

    void addParticle(Particle *particle);

    void addRigidBody(RigidBody *body);

    void addJoin(Join *join);

    void update(float dt);

    void clear();

    void setGravity(const Vector2f newGravity) { gravity = newGravity; };

    [[nodiscard]] const std::vector<Particle *> &GetParticles() const { return particles; };

    [[nodiscard]] const std::vector<RigidBody *> &GetRigidBodies() const { return rigidBodies; };

    [[nodiscard]] const std::vector<Join *> &GetJoins() const { return joins; };

private:
    void stepWorld(float dt);

    void stepObjects(float dt);

    void stepJoins(float dt) const;

    void applyGravity() const;

    void applyAirFriction() const;

    void detectCollisions();

    void broadPhase();

    void narrowPhase();

    void resolveCollisions(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision);

    Vector2f gravity;
    std::vector<CollisionPair> collisionPairs;

    std::vector<Particle *> particles;
    std::vector<RigidBody *> rigidBodies;
    std::vector<Join *> joins;
};
