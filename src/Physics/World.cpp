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

void World::addParticle(Particle *particle) {
    particles.push_back(particle);
}

void World::addRigidBody(RigidBody *body) {
    rigidBodies.push_back(body);
}

void World::addJoin(Join *join) {
    joins.push_back(join);
}

void World::update(const float dt) {
    stepWorld(dt);
}

void World::stepWorld(const float dt) {
    // natural physics modifications
    applyGravity();
    applyAirFriction();

    // objects update
    stepJoins(dt);
    stepObjects(dt);

    // collision detection
    detectCollisions();
}

void World::stepObjects(const float dt) {
    for (RigidBody *body: rigidBodies) {
        body->update(dt);
    }
}

void World::stepJoins(const float dt) const {
    for (const Join *join: joins) {
        join->update(dt);
    }
}

void World::applyGravity() const {
    for (RigidBody *body: rigidBodies) {
        if (!body->isInert()) {
            body->applyAcceleration(gravity);
        }
    }
}

void World::applyAirFriction() const {
    for (RigidBody *body: rigidBodies) {
        if (!body->isInert()) {
            body->setVelocity(body->getVelocity() * (1.0f - body->getFriction()));
        }
    }
}

void World::detectCollisions() {
    // preliminary detection
    broadPhase();

    // advanced detection
    NarrowPhase();
}

void World::broadPhase() {
    // Sweep and Prune
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

            if (bodyA->isInert() and bodyB->isInert()) continue;
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
