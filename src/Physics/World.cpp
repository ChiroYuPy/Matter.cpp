#include "Physics/World.h"

#include <iostream>
#include <ostream>

#include "Physics/Solver.h"
#include <vector>

World::World(Vector2f gravity) : gravity(gravity) {
}

void World::AddParticle(Particle *particle) {
    particles.push_back(particle);
}

void World::AddRigidBody(RigidBody *body) {
    rigidBodies.push_back(body);
}

void World::AddJoin(Join *join) {
    joins.push_back(join);
}

void World::Update(float dt) {
    StepWorld(dt);
}

void World::StepWorld(float dt) {
    // natural physics modifications
    ApplyGravity();

    // objects update
    StepJoins(dt);
    StepObjects(dt);

    // collision detection
    DetectCollisions();
}

void World::StepObjects(float dt) {
    for (RigidBody *body: rigidBodies) {
        body->Update(dt);
    }
}

void World::StepJoins(float dt) {
    for (Join *join: joins) {
        join->update(dt);
    }
}

void World::ApplyGravity() const {
    for (RigidBody *body: rigidBodies) {
        if (!body->IsInert()) {
            body->ApplyAcceleration(gravity);
        }
    }
}

void World::DetectCollisions() {
    // preliminary detection
    BroadPhase();

    // advanced detection
    NarrowPhase();
}

void World::BroadPhase() {
    collisionPairs.clear();

    for (size_t i = 0; i < rigidBodies.size(); ++i) {
        for (size_t j = i + 1; j < rigidBodies.size(); ++j) {
            RigidBody *bodyA = rigidBodies[i];
            RigidBody *bodyB = rigidBodies[j];

            if (bodyA->IsInert() and bodyB->IsInert()) continue;

            if (!bodyA->GetAABB().intersect(bodyB->GetAABB())) continue;

            collisionPairs.emplace_back(bodyA, bodyB);
        }
    }
}

void World::NarrowPhase() {
    for (const CollisionPair &pair: collisionPairs) {
        CollisionInfo collision = Collisioner::TestCollision(pair.bodyA, pair.bodyB);
        if (collision.collided) {
            Solver::ResolveCollision(pair.bodyA, pair.bodyB, collision);
        }
    }
}

void World::Clear() {
    for (const Particle *p: particles) {
        delete p;
    }
    particles.clear();

    for (const RigidBody *rb: rigidBodies) {
        delete rb;
    }
    rigidBodies.clear();

    for (const Join *j: joins) {
        delete j;
    }
    joins.clear();

    collisionPairs.clear();
}
