//
// Created by adrian on 25/02/25.
//

#pragma once
#include "RigidBody.h"

class Ball : public RigidBody {
public:
    Ball(Vector2 position, float radius, float mass, float friction);

    void Update(float dt) override;
    AABB GetAABB() const override;
    float GetRadius() const;
    BodyType GetType() const override { return BodyType::Ball; }

private:
    float radius;
};
