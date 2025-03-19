//
// Created by adrian on 26/02/25.
//

#include "Physics/Objects/Join.h"
#include <cmath>

Join::Join(Particle& objA, Particle& objB, const float length, const float stiffness, const float damping)
    : objA(objA), objB(objB), length(length), stiffness(stiffness), damping(damping) {
}

void Join::update(const float dt) const {

    const Vector2 deltaP = objB.getPosition() - objA.getPosition();
  	const Vector2 deltaV = objB.getVelocity() - objA.getVelocity();

    const float distance = std::sqrt(deltaP.x * deltaP.x + deltaP.y * deltaP.y);
    if (distance == 0) return;

    const Vector2 direction = deltaP / distance;

    const float displacement = distance - length;
    const float spring_force_magnitude = displacement * stiffness;

    const float dot_product = direction.x * deltaV.x + direction.y * deltaV.y;
    const float damping_force_magnitude = dot_product * damping;

    const float total_force_magnitude = spring_force_magnitude + damping_force_magnitude;

    // if (total_force_magnitude > max_force && max_force != 0.f) {
    //     broken = true;
    // }

    const Vector2 force = direction * total_force_magnitude;
    objA.applyForce(force);
    objB.applyForce( - force);
}
