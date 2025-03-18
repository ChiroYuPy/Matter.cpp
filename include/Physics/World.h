//
// Created by adrian on 25/02/25.
//

#pragma once
#include <vector>
#include "Objects/Particle.h"
#include "Objects/RigidBody.h"
#include "Objects/Ball.h"
#include "Objects/Polygon.h"
#include "Objects/Box.h"
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
    explicit World(Vector2 gravity);

    void AddParticle(Particle *particle);

    void AddRigidBody(RigidBody *body);

    void AddJoin(Join *body);

    void Update(float dt);

    void Clear();

    void SetGravity(const Vector2 newGravity) { gravity = newGravity; };

    const std::vector<Particle *> &GetParticles() const { return particles; };

    const std::vector<RigidBody *> &GetRigidBodies() const { return rigidBodies; };

    const std::vector<Join *> &GetJoins() const { return joins; };

private:
    void StepWorld(float dt);

    void StepObjects(float dt);

    void StepJoins(float dt);

    void ApplyGravity() const;

    void DetectCollisions();

    void BroadPhase();

    void NarrowPhase();

    void ResolveCollisions(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision);

    Vector2 gravity;
    std::vector<CollisionPair> collisionPairs;

    std::vector<Particle *> particles;
    std::vector<RigidBody *> rigidBodies;
    std::vector<Join *> joins;
};
