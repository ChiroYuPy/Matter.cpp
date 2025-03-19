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

    CollisionPair(RigidBody *a, RigidBody *b) : bodyA(a), bodyB(b) {
    }
};

class World {
public:
    World();

    explicit World(Vector2f gravity);

    void AddParticle(Particle *particle);

    void AddRigidBody(RigidBody *body);

    void AddJoin(Join *join);

    void Update(float dt);

    void Clear();

    void SetGravity(const Vector2f newGravity) { gravity = newGravity; };

    [[nodiscard]] const std::vector<Particle *> &GetParticles() const { return particles; };

    [[nodiscard]] const std::vector<RigidBody *> &GetRigidBodies() const { return rigidBodies; };

    [[nodiscard]] const std::vector<Join *> &GetJoins() const { return joins; };

private:
    void StepWorld(float dt);

    void StepObjects(float dt);

    void StepJoins(float dt) const;

    void ApplyGravity() const;

    void ApplyAirFriction() const;

    void DetectCollisions();

    void BroadPhase();

    void NarrowPhase();

    void ResolveCollisions(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision);

    Vector2f gravity;
    std::vector<CollisionPair> collisionPairs;

    std::vector<Particle *> particles;
    std::vector<RigidBody *> rigidBodies;
    std::vector<Join *> joins;
};
