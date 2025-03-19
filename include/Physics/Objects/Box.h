//
// Created by adrian on 26/02/25.
//

#ifndef BOX_H
#define BOX_H

#include "Polygon.h"

class Box final : public Polygon {
    float width, height;

public:
    Box(const Vector2f &position, float width, float height);

    void update(float dt) override;
};

#endif // BOX_H
