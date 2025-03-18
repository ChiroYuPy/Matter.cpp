//
// Created by adrian on 25/02/25.
//

#include "Physics/Solver.h"

void Solver::ResolveCollision(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision) {
    ApplySeparation(bodyA, bodyB, collision);

    ApplyImpulse(bodyA, bodyB, collision);
}

void Solver::ApplySeparation(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision) {
    Vector2 separationVector = collision.normal * collision.depth;

    if (bodyA->IsInert()) {
        bodyB->SetPosition(bodyB->GetPosition() - separationVector);
    } else if (bodyB->IsInert()) {
        bodyA->SetPosition(bodyA->GetPosition() + separationVector);
    } else {
        bodyA->SetPosition(bodyA->GetPosition() + separationVector * 0.5f);
        bodyB->SetPosition(bodyB->GetPosition() - separationVector * 0.5f);
    }
}

void Solver::ApplyImpulse(RigidBody* bodyA, RigidBody* bodyB, const CollisionInfo& collision) {

    Vector2 relativeVelocity = bodyA->GetVelocity() - bodyB->GetVelocity();
    float velocityAlongNormal = relativeVelocity.Dot(collision.normal);

    if (velocityAlongNormal < 0) {
        float restitution = 1.f;
        float impulse = -(1 + restitution) * velocityAlongNormal;
        impulse /= (1 / bodyA->GetMass() + 1 / bodyB->GetMass());

        Vector2 impulseVector = collision.normal * impulse;
        bodyA->SetVelocity(bodyA->GetVelocity() + impulseVector / bodyA->GetMass());
        bodyB->SetVelocity(bodyB->GetVelocity() - impulseVector / bodyB->GetMass());
    }
}
