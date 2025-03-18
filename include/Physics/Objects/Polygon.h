//
// Created by adrian on 26/02/25.
//

#ifndef POLYGON_H
#define POLYGON_H

#include "RigidBody.h"
#include <vector>

class Polygon : public RigidBody {
protected:
    std::vector<Vector2f> vertices;

public:
    Polygon(const Vector2f& position, float mass, float friction, const std::vector<Vector2f>& verts);

    void Update(float dt) override;
    [[nodiscard]] AABB GetAABB() const override;
    [[nodiscard]] const std::vector<Vector2f>& GetVertices() const;
    [[nodiscard]] BodyType GetType() const override { return BodyType::Polygon; }
};

#endif // POLYGON_H
