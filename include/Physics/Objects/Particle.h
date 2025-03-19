//
// Created by adrian on 25/02/25.
//

#pragma once
#include "../../Math/Vector2.h"

class Particle {
public:
    virtual ~Particle() = default;

    Particle(Vector2f position);

    void applyForce(const Vector2f &force);

    void applyAcceleration(const Vector2f &force);

    virtual void update(float dt);

    [[nodiscard]] Vector2f getPosition() const;
    void setPosition(Vector2f newPosition);

    [[nodiscard]] Vector2f getVelocity() const;
    void setVelocity(Vector2f newPosition);
    
    [[nodiscard]] bool isInert() const;
    void setInert(bool newInert);

    [[nodiscard]] bool isActive() const;
    void setActive(bool newActive);

    [[nodiscard]] float getMass() const;
    void setMass(float newMass);

protected:
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    bool inert;
    bool active;
    float mass;
};
