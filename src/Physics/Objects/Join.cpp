//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Join.h"
#include <cmath>

Join::Join(Particle& objA, Particle& objB, float length, float stiffness, float damping)
    : objA(objA), objB(objB), length(length), stiffness(stiffness), damping(damping) {
}

void Join::update(float dt) {

    Vector2 deltaP = objB.GetPosition() - objA.GetPosition();
  	Vector2 deltaV = objB.GetVelocity() - objA.GetVelocity();

    float distance = std::sqrt(deltaP.x * deltaP.x + deltaP.y * deltaP.y);
    if (distance == 0) return;

    Vector2 direction = deltaP / distance;

    float displacement = distance - length;
    float spring_force_magnitude = displacement * stiffness;

    float dot_product = direction.x * deltaV.x + direction.y * deltaV.y;
    float damping_force_magnitude = dot_product * damping;

    float total_force_magnitude = spring_force_magnitude + damping_force_magnitude;

    // if (total_force_magnitude > max_force && max_force != 0.f) {
    //     broken = true;
    // }

    Vector2 force = direction * total_force_magnitude;
    objA.ApplyForce(force);
    objB.ApplyForce( - force);
}
