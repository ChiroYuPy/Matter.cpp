//
// Created by adrian on 25/02/25.
//

#pragma once
#include "../../Math/Vector2.h"

class Particle {
public:
    virtual ~Particle() = default;

    Particle(Vector2f position, float mass);

    void ApplyForce(const Vector2f &force);

    void ApplyAcceleration(const Vector2f &force);

    virtual void Update(float dt);

    [[nodiscard]] Vector2f GetPosition() const { return position; };
    void SetPosition(const Vector2f newPosition) { position = newPosition; };

    [[nodiscard]] Vector2f GetVelocity() const { return velocity; };
    void SetVelocity(const Vector2f newPosition) { velocity = newPosition; };
    
    [[nodiscard]] bool IsInert() const { return inert; };
    void SetInert(const bool newInert) { inert = newInert; };

    [[nodiscard]] bool IsActive() const { return active; };
    void SetActive(const bool newActive) { active = newActive; };

    [[nodiscard]] float GetMass() const { return mass; };
    void SetMass(const float newMass) { mass = newMass; };

protected:
    Vector2f position;
    Vector2f velocity;
    Vector2f acceleration;
    bool inert;
    bool active;
    float mass;
};
