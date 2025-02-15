//
// Created by adrian on 14/02/25.
//

#ifndef CONSTRAINT_H
#define CONSTRAINT_H

#include "Particle.h"

class Constraint {
public:
  Constraint(Particle &objA, Particle &objB, float length, float stiffness, float damping);

  void update(float dt);

  Particle getObjA() const { return objA; }
  Particle getObjB() const { return objB; }

private:
  Particle &objA;
  Particle &objB;
  float length;
  float stiffness;
  float damping;
};

#endif //CONSTRAINT_H
