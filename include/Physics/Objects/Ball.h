//
// Created by adrian on 25/02/25.
//

#pragma once
#include "RigidBody.h"

class Ball final : public RigidBody {
public:
    Ball(Vector2f position, float radius, float mass, float friction);

    void update(float dt) override;

    [[nodiscard]] AABB getAABB() const override;

    [[nodiscard]] float GetRadius() const;

    [[nodiscard]] BodyType GetType() const override { return BodyType::Ball; }

private:
    float radius;
};
