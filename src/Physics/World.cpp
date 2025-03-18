#include "Physics/World.h"

#include <algorithm>

#include "Physics/Solver.h"
#include <vector>

struct SAPEntry {
    float minX;
    float maxX;
    RigidBody* body;

    bool operator<(const SAPEntry& other) const {
        return minX < other.minX;
    }
};


World::World(const Vector2f gravity) : gravity(gravity) {
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

void World::Update(const float dt) {
    StepWorld(dt);
}

void World::StepWorld(const float dt) {
    // natural physics modifications
    ApplyGravity();
    ApplyAirFriction();

    // objects update
    StepJoins(dt);
    StepObjects(dt);

    // collision detection
    DetectCollisions();
}

void World::StepObjects(const float dt) {
    for (RigidBody *body: rigidBodies) {
        body->update(dt);
    }
}

void World::StepJoins(const float dt) const {
    for (const Join *join: joins) {
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

void World::ApplyAirFriction() const {
    for (RigidBody *body: rigidBodies) {
        if (!body->IsInert()) {
            body->getVelocity(body->getVelocity() * (1.0f - body->getFriction()));
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
    std::vector<SAPEntry> sapList;

    // Remplir la liste avec les AABB de tous les objets
    for (RigidBody* body : rigidBodies) {
        AABB aabb = body->getAABB();
        sapList.push_back({aabb.getMin().x, aabb.getMax().x, body});
    }

    // Trier par minX
    std::sort(sapList.begin(), sapList.end());

    // Balayage pour détecter les paires en collision
    for (size_t i = 0; i < sapList.size(); ++i) {
        for (size_t j = i + 1; j < sapList.size(); ++j) {
            // Optimisation : si le minX du second dépasse le maxX du premier, on arrête
            if (sapList[j].minX > sapList[i].maxX) break;

            RigidBody* bodyA = sapList[i].body;
            RigidBody* bodyB = sapList[j].body;

            // Vérification réelle de la collision avec les AABB

            if (bodyA->IsInert() and bodyB->IsInert()) continue;
            if (!bodyA->getAABB().intersect(bodyB->getAABB())) continue;

            collisionPairs.emplace_back(bodyA, bodyB);
        }
    }
}

void World::NarrowPhase() {
    for (const CollisionPair &pair: collisionPairs) {
        if (CollisionInfo collision = Collisioner::TestCollision(pair.bodyA, pair.bodyB); collision.collided) {
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
