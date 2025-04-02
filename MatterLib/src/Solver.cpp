//
// Created by adrian on 25/02/25.
//

#include "MATTER/Solver.h"

void Solver::ResolveCollision(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    ApplySeparation(bodyA, bodyB, collision);

    ApplyImpulse(bodyA, bodyB, collision);
}

void Solver::ApplySeparation(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    const Vector2f separationVector = collision.normal * collision.depth;

    if (bodyA->isInert()) {
        bodyB->setPosition(bodyB->getPosition() - separationVector);
    } else if (bodyB->isInert()) {
        bodyA->setPosition(bodyA->getPosition() + separationVector);
    } else {
        bodyA->setPosition(bodyA->getPosition() + separationVector * 0.5f);
        bodyB->setPosition(bodyB->getPosition() - separationVector * 0.5f);
    }
}

void Solver::ApplyImpulse(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    const Vector2f relativeVelocity = bodyA->getVelocity() - bodyB->getVelocity();

    if (const float velocityAlongNormal = Vector2f::Dot(relativeVelocity, collision.normal); velocityAlongNormal < 0) {
        const float restitution = std::min(bodyA->getRestitution(), bodyB->getRestitution());
        float impulse = -(1 + restitution) * velocityAlongNormal;
        impulse /= (1 / bodyA->getMass() + 1 / bodyB->getMass());

        const Vector2f impulseVector = collision.normal * impulse;
        bodyA->setVelocity(bodyA->getVelocity() + impulseVector / bodyA->getMass());
        bodyB->setVelocity(bodyB->getVelocity() - impulseVector / bodyB->getMass());
    }
}
