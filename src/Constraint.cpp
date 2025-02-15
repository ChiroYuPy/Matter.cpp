//
// Created by adrian on 14/02/25.
//

#include "../header/Constraint.h"
#include "../header/Utils.h"

Constraint::Constraint(Particle& objA, Particle& objB, float length, float stiffness, float damping)
    : objA(objA), objB(objB), length(length), stiffness(stiffness), damping(damping) {
}

void Constraint::update(float dt) {
    // Calculer la différence de position entre les deux particules
    sf::Vector2f deltaP = objB.getPosition() - objA.getPosition();
    // Calculer la différence de vitesse entre les deux particules
    sf::Vector2f deltaV = objB.getVelocity() - objA.getVelocity();

    // Calculer la distance entre les particules
    float distance = std::sqrt(deltaP.x * deltaP.x + deltaP.y * deltaP.y);
    if (distance == 0) return;  // Eviter division par zéro

    // Normaliser la direction du vecteur
    sf::Vector2f direction = deltaP / distance;

    // Calculer le déplacement par rapport à la longueur du ressort
    float displacement = distance - length;
    // Calculer la force du ressort en fonction du déplacement et de la raideur
    float spring_force_magnitude = displacement * stiffness;

    // Calculer la force de damping (amortissement) en fonction de la vitesse relative
    float dot_product = direction.x * deltaV.x + direction.y * deltaV.y;
    float damping_force_magnitude = dot_product * damping;

    // Calculer la force totale en additionnant la force du ressort et la force de damping
    float total_force_magnitude = spring_force_magnitude + damping_force_magnitude;

    // Si la force dépasse un seuil maximal (non implémenté pour l'instant), la contrainte peut être rompue
    // if (total_force_magnitude > max_force && max_force != 0.f) {
    //     broken = true;
    // }

    // Appliquer la force sur les deux particules, une force est positive et l'autre négative pour "tirer" sur elles
    sf::Vector2f force = direction * total_force_magnitude;
    objA.applyForce(force);
    objB.applyForce(-force);
}
