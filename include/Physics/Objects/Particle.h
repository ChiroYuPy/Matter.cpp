//
// Created by adrian on 25/02/25.
//

#pragma once
#include "../../Math/Vector2.h"

class Particle {
public:
    virtual ~Particle() = default;

    Particle(Vector2f position, float mass);

    void applyForce(const Vector2f &force);

    void applyAcceleration(const Vector2f &force);

    virtual void update(float dt);

    [[nodiscard]] Vector2f getPosition() const { return position; };
    void setPosition(const Vector2f newPosition) { position = newPosition; };

    [[nodiscard]] Vector2f getVelocity() const { return velocity; };
    void setVelocity(const Vector2f newPosition);;
    
    [[nodiscard]] bool isInert() const { return inert; };
    void setInert(const bool newInert) { inert = newInert; };

    [[nodiscard]] bool isActive() const { return active; };
    void setActive(const bool newActive) { active = newActive; };

    [[nodiscard]] float getMass() const { return mass; };
    void setMass(const float newMass) { mass = newMass; };

protected:
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    bool inert;
    bool active;
    float mass;
};
