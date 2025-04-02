//
// Created by adrian on 25/02/25.
//

#pragma once

#ifndef BALL_H
#define BALL_H

#include "MATTER/objects/RigidBody.h"

class Ball : public RigidBody {
public:
    Ball(Vector2f position, float friction);

    void update(float dt) override;

    [[nodiscard]] AABB getAABB() const override;

    [[nodiscard]] float getRadius() const;

    [[nodiscard]] BodyType getType() const override;

private:
    float radius;
};

#endif //BALL_H