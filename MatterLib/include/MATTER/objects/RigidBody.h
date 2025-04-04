//
// Created by adrian on 25/02/25.
//

#pragma once

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include "MATTER/objects/Particle.h"
#include "MATTER/math/AABB.h"

enum class BodyType { Ball, Polygon };

class RigidBody : public Particle {
public:
    explicit RigidBody(Vector2f position);

    [[nodiscard]] virtual AABB getAABB() const = 0;

    [[nodiscard]] virtual BodyType getType() const = 0;

    void setRestitution(float newRestitution);
    [[nodiscard]] float getRestitution() const;

    void setFriction(float newFriction);
    [[nodiscard]] float getFriction() const;

    void setAngle(float newAngle);
    [[nodiscard]] float getAngle() const;

    void setAngularVelocity(float newAngularVelocity);
    [[nodiscard]] float getAngularVelocity() const;

    void setInertia(float newInertia);
    [[nodiscard]] float getInertia() const;
    [[nodiscard]] float getInvertedInertia() const;

protected:
    [[nodiscard]] virtual float calculateInertia() const;

    float restitution;
    float friction;
    float angle;
    float angularVelocity;
    float inertia;
    float invertedInertia;
};

#endif // RIGIDBODY_H