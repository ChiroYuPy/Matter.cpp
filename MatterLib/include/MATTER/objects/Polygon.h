//
// Created by adrian on 26/02/25.
//

#include <vector>

#ifndef POLYGON_H
#define POLYGON_H

#include "MATTER/objects/RigidBody.h"

class Polygon : public RigidBody {
protected:
    std::vector<Vector2f> vertices;
    mutable std::vector<Vector2f> rotatedVertices;

public:
    Polygon(const Vector2f &position, const std::vector<Vector2f> &verts);

    void update(float dt) override;

    [[nodiscard]] AABB getAABB() const override;

    [[nodiscard]] std::vector<Vector2f> getVertices() const;

    [[nodiscard]] BodyType getType() const override { return BodyType::Polygon; }
};

#endif // POLYGON_H
