//
// Created by adrian on 26/02/25.
//

#ifndef JOIN_H
#define JOIN_H

#include "Particle.h"

class Join {
public:
    Join(Particle &objA, Particle &objB, float length, float stiffness, float damping);

    void update(float dt) const;

    Particle *GetBodyA() const { return &objA; }
    Particle *GetBodyB() const { return &objB; }

private:
    Particle &objA;
    Particle &objB;
    float length;
    float stiffness;
    float damping;
};


#endif //JOIN_H
