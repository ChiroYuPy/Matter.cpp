//
// Created by adrian on 26/02/25.
//

#ifndef POLYGON_H
#define POLYGON_H

#include "RigidBody.h"
#include <vector>

class Polygon : public RigidBody {
protected:
    std::vector<Vector2> vertices;

public:
    Polygon(const Vector2& position, float mass, float friction, const std::vector<Vector2>& verts);

    void Update(float dt) override;
    AABB GetAABB() const override;
    const std::vector<Vector2>& GetVertices() const;
    BodyType GetType() const override { return BodyType::Polygon; }
};

#endif // POLYGON_H
