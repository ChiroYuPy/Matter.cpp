//
// Created by adrian on 25/02/25.
//

#pragma once
#include "Objects/RigidBody.h"
#include "Objects/Ball.h"
#include "Objects/Polygon.h"

struct CollisionInfo {
    bool collided{};
    Vector2f normal;
    float depth{};
};

class Collisioner {
public:
    static CollisionInfo TestCollision(RigidBody* rb1, RigidBody* rb2);

private:
    static CollisionInfo TestBallsCollision(const Ball *ball1, const Ball *ball2);

    static CollisionInfo TestBallPolygonCollision(const Ball *ball, const Polygon *poly);

    static CollisionInfo TestPolygonsCollision(const Polygon *poly1, const Polygon *poly2);

    static std::pair<float, float> projectVertices(const std::vector<Vector2f> &vertices, const Vector2f &axis);

    static std::pair<float, float> projectCircle(const Vector2f &center, float radius, const Vector2f &axis);

    static size_t findClosestPointOnPolygon(const Vector2f &circleCenter, const std::vector<Vector2f> &vertices);
};
