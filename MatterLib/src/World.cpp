#include "MATTER/World.h"

#include <algorithm>

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
    static float accumulatedTime = 0.0f;
    accumulatedTime += dt;

    int updatesThisFrame = 0;

    const float dividedDeltaTime = 1.f / static_cast<float>(updatePerSeconds);

    while (accumulatedTime >= dividedDeltaTime && updatesThisFrame < maxUpdatePerFrame) {

        // Modifications physiques naturelles
        applyGravity();
        applyAirFriction();

        // Mise à jour des objets et des jointures
        stepJoins(dividedDeltaTime);
        stepObjects(dividedDeltaTime);

        // Détection des collisions
        detectCollisions();

        accumulatedTime -= dividedDeltaTime;
        updatesThisFrame++;
    }
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
    narrowPhase();
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

void World::narrowPhase() {
    collisionInfos.clear();
    for (const CollisionPair &pair: collisionPairs) {
        if (CollisionInfo collision = Collisioner::TestCollision(pair.bodyA, pair.bodyB); collision.collided) {
            Solver::ResolveCollision(pair.bodyA, pair.bodyB, collision);
            collisionInfos.emplace_back(collision);
        }
    }
}

void World::clear() {
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

void World::setUpdatePerSeconds(const int newUpdatePerSeconds) { updatePerSeconds = newUpdatePerSeconds; }

void World::setMaxUpdatePerFrame(const int newMaxUpdatePerFrame) { maxUpdatePerFrame = newMaxUpdatePerFrame; }

void World::setGravity(const Vector2f newGravity) { gravity = newGravity; }

[[nodiscard]] const std::vector<Particle *>& World::GetParticles() const { return particles; }

[[nodiscard]] const std::vector<RigidBody *>& World::GetRigidBodies() const { return rigidBodies; }

[[nodiscard]] const std::vector<Join *>& World::GetJoins() const { return joins; }

[[nodiscard]] const std::vector<CollisionInfo>& World::GetCollisionInfos() const { return collisionInfos; }