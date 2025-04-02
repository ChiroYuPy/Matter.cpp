#include "MATTER/Collisioner.h"
#include <cmath>

CollisionInfo Collisioner::TestCollision(RigidBody *rb1, RigidBody *rb2) {
    auto collisionInfo = CollisionInfo(false, Vector2f(), 0.0f);

    if (const auto *ball1 = dynamic_cast<Ball *>(rb1)) {
        if (const auto *ball2 = dynamic_cast<Ball *>(rb2)) {
            collisionInfo = TestBallsCollision(ball1, ball2);
        } else if (const auto *poly2 = dynamic_cast<Polygon *>(rb2)) {
            collisionInfo = TestBallPolygonCollision(ball1, poly2);
            collisionInfo.normal = -collisionInfo.normal;
        }
    } else if (const auto *poly1 = dynamic_cast<Polygon *>(rb1)) {
        if (const auto *ball2 = dynamic_cast<Ball *>(rb2)) {
            collisionInfo = TestBallPolygonCollision(ball2, poly1);
        } else if (const auto *poly2 = dynamic_cast<Polygon *>(rb2)) {
            collisionInfo = TestPolygonsCollision(poly1, poly2);
        }
    }

    return collisionInfo;
}

CollisionInfo Collisioner::TestBallsCollision(const Ball *ball1, const Ball *ball2) {
    const Vector2f distance = ball1->getPosition() - ball2->getPosition();
    const float radiusSum = ball1->getRadius() + ball2->getRadius();
    const float distLength = Vector2f::Length(distance);

    if (distLength <= radiusSum) {
        const Vector2 normal = distance / distLength;
        const float depth = radiusSum - distLength;
        return CollisionInfo(true, normal, depth);
    }

    return CollisionInfo(false, Vector2f(), 0.0f);
}

CollisionInfo Collisioner::TestBallPolygonCollision(const Ball *ball, const Polygon *poly) {
    const std::vector<Vector2f> &vertices = poly->getVertices();
    const Vector2f ballPos = ball->getPosition();
    const float ballRadius = ball->getRadius();

    Vector2f normal(0, 0);
    float depth = std::numeric_limits<float>::infinity();

    // Test collision with each edge of the polygon
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector2f va = vertices[i];
        Vector2f vb = vertices[(i + 1) % vertices.size()];
        const Vector2f edge = vb - va;
        Vector2f axis(-edge.y, edge.x);
        axis = Vector2f::Normalize(axis);

        auto [minA, maxA] = projectVertices(vertices, axis);
        auto [minB, maxB] = projectCircle(ballPos, ballRadius, axis);

        if (minA >= maxB || minB >= maxA) {
            return CollisionInfo(false, Vector2f(), 0.0f);
        }

        if (const float axisDepth = std::min(maxB - minA, maxA - minB); axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    // Find the closest point on the polygon to the ball center
    const size_t cpIndex = findClosestPointOnPolygon(ballPos, vertices);
    const Vector2f cp = vertices[cpIndex];

    Vector2f axis = cp - ballPos;
    axis = Vector2f::Normalize(axis);

    auto [minA, maxA] = projectVertices(vertices, axis);
    auto [minB, maxB] = projectCircle(ballPos, ballRadius, axis);

    if (minA >= maxB || minB >= maxA) {
        return CollisionInfo(false, Vector2f(), 0.0f);
    }

    if (const float axisDepth = std::min(maxB - minA, maxA - minB); axisDepth < depth) {
        depth = axisDepth;
        normal = axis;
    }

    // Adjust normal direction
    const Vector2f direction = poly->getPosition() - ballPos;
    if (Vector2f::Dot(normal, direction) < 0) {
        normal = -normal;
    }

    return CollisionInfo(true, normal, depth);
}

CollisionInfo Collisioner::TestPolygonsCollision(const Polygon *poly1, const Polygon *poly2) {
    const std::vector<Vector2f> &vertices1 = poly1->getVertices();
    const std::vector<Vector2f> &vertices2 = poly2->getVertices();

    Vector2f normal;
    float depth = std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < vertices1.size(); ++i) {
        Vector2f va = vertices1[i];
        Vector2f vb = vertices1[(i + 1) % vertices1.size()];
        const Vector2f edge = vb - va;
        Vector2f axis(-edge.y, edge.x);
        axis = Vector2f::Normalize(axis);

        auto [minA1, maxA1] = projectVertices(vertices1, axis);
        auto [minB1, maxB1] = projectVertices(vertices2, axis);

        if (maxA1 < minB1 || maxB1 < minA1) {
            return CollisionInfo(false, normal, depth);
        }

        if (const float axisDepth = std::min(maxB1 - minA1, maxA1 - minB1); axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    for (size_t i = 0; i < vertices2.size(); ++i) {
        Vector2f va = vertices2[i];
        Vector2f vb = vertices2[(i + 1) % vertices2.size()];
        const Vector2f edge = vb - va;
        Vector2f axis(-edge.y, edge.x);
        axis = Vector2f::Normalize(axis);

        auto [minA2, maxA2] = projectVertices(vertices1, axis);
        auto [minB2, maxB2] = projectVertices(vertices2, axis);

        if (maxA2 < minB2 || maxB2 < minA2) {
            return CollisionInfo(false, normal, depth);
        }

        if (const float axisDepth = std::min(maxB2 - minA2, maxA2 - minB2); axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    return CollisionInfo(true, normal, depth);
}

std::pair<float, float> Collisioner::projectVertices(const std::vector<Vector2f>& vertices, const Vector2f& axis) {
    float minProj = std::numeric_limits<float>::infinity();
    float maxProj = -std::numeric_limits<float>::infinity();

    for (const Vector2f& v : vertices) {
        float proj = Vector2f::Dot(v, axis);
        minProj = std::min(minProj, proj);
        maxProj = std::max(maxProj, proj);
    }

    return {minProj, maxProj};
}

std::pair<float, float> Collisioner::projectCircle(const Vector2f &center, float radius, const Vector2f &axis) {
    const Vector2f direction = Vector2f::Normalize(axis);
    const auto directionAndRadius = direction * radius;

    const Vector2f p1 = center + directionAndRadius;
    const Vector2f p2 = center - directionAndRadius;

    float minProj = Vector2f::Dot(p1, axis);
    float maxProj = Vector2f::Dot(p2, axis);

    if (minProj > maxProj) std::swap(minProj, maxProj);

    return {minProj, maxProj};
}

size_t Collisioner::findClosestPointOnPolygon(const Vector2f &circleCenter, const std::vector<Vector2f> &vertices) {
    size_t result = 0;
    float minDistance = std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < vertices.size(); ++i) {
        const auto distance = Vector2f::Length(vertices[i] - circleCenter);

        if (distance < minDistance) {
            minDistance = distance;
            result = i;
        }
    }

    return result;
}
