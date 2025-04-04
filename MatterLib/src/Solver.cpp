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

/*
void Solver::ApplyImpulse(RigidBody *bodyA, RigidBody *bodyB, const CollisionInfo &collision) {
    // Vitesse relative entre les deux corps
    Vector2f relativeVelocity = bodyA->getVelocity() - bodyB->getVelocity();

    // Si la vitesse relative dans la direction de la normale de collision est positive, les corps s'éloignent
    float velocityAlongNormal = Vector2f::Dot(relativeVelocity, collision.normal);
    if (velocityAlongNormal > 0) {
        return;  // Aucun besoin de résoudre la collision, les corps s'éloignent
    }

    // Calcul de la restitution
    float restitution = std::min(bodyA->getRestitution(), bodyB->getRestitution());

    // Calcul de l'impulsion
    float impulseMagnitude = -(1.0f + restitution) * velocityAlongNormal;
    float inverseMassSum = (1.0f / bodyA->getMass()) + (1.0f / bodyB->getMass());

    // Calcul de l'impulsion en fonction des masses
    impulseMagnitude /= inverseMassSum;

    // Parcours des points de contact pour appliquer l'impulsion
    for (const auto& contact : collision.contacts) {
        // Vecteurs du centre de masse au point de contact
        Vector2f ra = contact - bodyA->getPosition();
        Vector2f rb = contact - bodyB->getPosition();

        // Calcul de l'impulsion dans la direction de la normale
        Vector2f impulse = collision.normal * impulseMagnitude;

        // Application de l'impulsion aux vitesses linéaires
        bodyA->setVelocity(bodyA->getVelocity() + impulse / bodyA->getMass());
        bodyB->setVelocity(bodyB->getVelocity() - impulse / bodyB->getMass());

        // Prise en compte de la rotation (moment d'impulsion)
        // Pour bodyA
        Vector2f raPerp(-ra.y, ra.x);  // Vecteur perpendiculaire à ra
        bodyA->setAngularVelocity(bodyA->getAngularVelocity() - Vector2f::Cross(raPerp, impulse) * bodyA->getInvertedInertia());

        // Pour bodyB
        Vector2f rbPerp(-rb.y, rb.x);  // Vecteur perpendiculaire à rb
        bodyB->setAngularVelocity(bodyB->getAngularVelocity() + Vector2f::Cross(rbPerp, impulse) * bodyB->getInvertedInertia());
    }
}
*/