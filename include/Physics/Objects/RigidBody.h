//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Particle.h"
#include "../../Math/AABB.h"

enum class BodyType { Ball, Polygon };

class RigidBody : public Particle {
public:
    RigidBody(Vector2f position);

    [[nodiscard]] virtual AABB getAABB() const = 0;

    [[nodiscard]] virtual BodyType getType() const = 0;

    void setRestitution(float newRestitution);

    [[nodiscard]] float getRestitution() const;

    void setFriction(float newFriction);

    [[nodiscard]] float getFriction() const;

    void setAngle(float newAngle);

    [[nodiscard]] float getAngle() const;

protected:
    float restitution;
    float friction;
    float angle;
};
