//
// Created by adrian on 25/02/25.
//

#include "Physics/Solver.h"

void Solver::ResolveCollision(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    ApplySeparation(bodyA, bodyB, collision);

    ApplyImpulse(bodyA, bodyB, collision);
}

void Solver::ApplySeparation(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    const Vector2f separationVector = collision.normal * collision.depth;

    if (bodyA->IsInert()) {
        bodyB->SetPosition(bodyB->GetPosition() - separationVector);
    } else if (bodyB->IsInert()) {
        bodyA->SetPosition(bodyA->GetPosition() + separationVector);
    } else {
        bodyA->SetPosition(bodyA->GetPosition() + separationVector * 0.5f);
        bodyB->SetPosition(bodyB->GetPosition() - separationVector * 0.5f);
    }
}

void Solver::ApplyImpulse(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    const Vector2f relativeVelocity = bodyA->getVelocity() - bodyB->getVelocity();

    if (const float velocityAlongNormal = Vector2f::Dot(relativeVelocity, collision.normal); velocityAlongNormal < 0) {
        constexpr float restitution = 1.f;
        float impulse = -(1 + restitution) * velocityAlongNormal;
        impulse /= (1 / bodyA->GetMass() + 1 / bodyB->GetMass());

        const Vector2f impulseVector = collision.normal * impulse;
        bodyA->getVelocity(bodyA->getVelocity() + impulseVector / bodyA->GetMass());
        bodyB->getVelocity(bodyB->getVelocity() - impulseVector / bodyB->GetMass());
    }
}
