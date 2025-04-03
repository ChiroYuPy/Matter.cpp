//
// Created by adrian on 25/02/25.
//

#pragma once

#ifndef COLLISIONER_H
#define COLLISIONER_H

#include "MATTER/objects/RigidBody.h"
#include "MATTER/objects/Ball.h"
#include "MATTER/objects/Polygon.h"
#include "MATTER/objects/Box.h"
#include "MATTER/CollisionInfo.h"

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

    static Vector2f findBallsContactPoint(const Ball *rb1, const Ball *rb2);
    static Vector2f findBallPolygonContactPoint(const Ball *rb1, const Polygon *rb2);
    static std::pair<Vector2f, Vector2f> findPolygonsContactPoints(const Polygon *rb1, const Polygon *rb2);
};

#endif // COLLISIONER_H