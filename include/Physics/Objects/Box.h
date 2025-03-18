//
// Created by adrian on 26/02/25.
//

#ifndef BOX_H
#define BOX_H

#include "Polygon.h"

class Box : public Polygon {
private:
    float width, height;

public:
    Box(const Vector2& position, float width, float height, float mass, float friction);

    void Update(float dt) override;
};

#endif // BOX_H
