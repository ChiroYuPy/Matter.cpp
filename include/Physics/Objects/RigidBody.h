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

    virtual void Update(float dt) override;

    virtual AABB GetAABB() const = 0;

    virtual BodyType GetType() const = 0;

    void SetFriction(float newFriction);

    float GetFriction() const;

protected:
    float friction;
};
