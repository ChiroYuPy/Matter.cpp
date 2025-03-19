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

    int updatePerSeconds = 1;
    int maxUpdatePerFrame = 16;

    Vector2f gravity;

    std::vector<CollisionPair> collisionPairs;

    std::vector<Particle *> particles;
    std::vector<RigidBody *> rigidBodies;
    std::vector<Join *> joins;
};
