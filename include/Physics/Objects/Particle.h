//
// Created by adrian on 25/02/25.
//

#pragma once
#include "../../Math/Vector2.h"

class Particle {
public:
    virtual ~Particle() = default;

    Particle(Vector2 position, float mass);

    void ApplyForce(const Vector2 &force);

    void ApplyAcceleration(const Vector2 &force);

    virtual void Update(float dt);

    Vector2 GetPosition() const { return position; };
    void SetPosition(Vector2 newPosition) { position = newPosition; };

    Vector2 GetVelocity() const { return velocity; };
    void SetVelocity(Vector2 newPosition) { velocity = newPosition; };
    
    bool IsInert() const { return inert; };
    void SetInert(bool newInert) { inert = newInert; };

    bool IsActive() const { return active; };
    void SetActive(bool newActive) { active = newActive; };

    float GetMass() const { return mass; };
    void SetMass(float newMass) { mass = newMass; };

protected:
    Vector2 position;
    Vector2 velocity;
    Vector2 acceleration;
    bool inert;
    bool active;
    float mass;
};
