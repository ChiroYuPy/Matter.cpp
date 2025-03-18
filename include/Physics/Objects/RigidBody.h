//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Particle.h"
#include "../../Math/AABB.h"

enum class BodyType { Ball, Polygon };

class RigidBody : public Particle {
public:
    RigidBody(Vector2f position, float mass, float friction);

    [[nodiscard]] virtual AABB GetAABB() const = 0;

    [[nodiscard]] virtual BodyType GetType() const = 0;

    void SetFriction(float newFriction);

    [[nodiscard]] float getFriction() const;

protected:
    float friction;
};
