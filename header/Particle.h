//
// Created by adrian on 07/02/25.
//

#ifndef PARTICLE_H
#define PARTICLE_H

#include <SFML/Graphics.hpp>

class Particle {
public:
    Particle(float x, float y, float radius);

    Particle(float x, float y, float radius, float mass, bool inert);

    void update(float dt);

    void applyForce(const sf::Vector2f &force);

    void applyTorque(float torque);

    void handleWallCollisions(const sf::RenderWindow &window);

    void draw(sf::RenderWindow &window) const;

    sf::Vector2f getPosition() const;

    void setPosition(const sf::Vector2f &position);

    sf::Vector2f getVelocity() const;

    void setVelocity(const sf::Vector2f &velocity);

    float getRadius() const;

    float getMass() const;

    float getInvMass() const;

    float getAngle() const;

    void setInert(bool ine);

    bool isInert() const;

    bool operator==(const Particle & other) const = default;

private:
    sf::Vector2f position = sf::Vector2f(0.f, 0.f);
    sf::Vector2f velocity = sf::Vector2f(0.f, 0.f);
    sf::Vector2f acceleration = sf::Vector2f(0.f, 0.f);

    bool inert = false;

    float radius;
    float mass = 1.f;
    float invMass = 1.f;
    float restitution = 1.f;
    float damping = 0.99;

    float angle = 0.f;
    float angularVelocity = 0.f;
    float angularAcceleration = 0.f;
    float momentOfInertia = 0.f;
    float angularDamping = 0.98;
};

#endif // PARTICLE_H
