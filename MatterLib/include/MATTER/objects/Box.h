//
// Created by adrian on 26/02/25.
//

#pragma once

#ifndef BOX_H
#define BOX_H

#include "MATTER/objects/Polygon.h"

class Box : public Polygon {
    float width, height;

public:
    Box(const Vector2f &position, float width, float height);

    void update(float dt) override;

    float getWidth() const;
    float getHeight() const;
};

#endif // BOX_H
