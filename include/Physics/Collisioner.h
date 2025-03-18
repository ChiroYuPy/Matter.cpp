//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Objects/RigidBody.h"
#include "Objects/Ball.h"
#include "Objects/Polygon.h"

struct CollisionInfo {
    bool collided{};
    Vector2 normal;
    float depth{};
};

class Collisioner {
public:
    static CollisionInfo TestCollision(RigidBody* rb1, RigidBody* rb2);

private:
    static CollisionInfo TestBallsCollision(const Ball *ball1, const Ball *ball2);

    static CollisionInfo TestBallPolygonCollision(const Ball *ball, const Polygon *poly);

    static CollisionInfo TestPolygonsCollision(const Polygon *poly1, const Polygon *poly2);

    static std::pair<float, float> projectVertices(const std::vector<Vector2> &vertices, const Vector2 &axis);

    static std::pair<float, float> projectCircle(const Vector2 &center, float radius, const Vector2 &axis);

    static size_t findClosestPointOnPolygon(const Vector2 &circleCenter, const std::vector<Vector2> &vertices);
};
