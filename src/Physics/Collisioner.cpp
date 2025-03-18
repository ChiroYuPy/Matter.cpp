#include "Physics/Collisioner.h"
#include <cmath>
#include "Physics/Objects/Box.h"
#include <iostream>

CollisionInfo Collisioner::TestCollision(RigidBody* rb1, RigidBody* rb2) {
    auto collisionInfo = CollisionInfo(false, Vector2(), 0.0f);

    if (auto* ball1 = dynamic_cast<Ball*>(rb1)) {
        if (auto* ball2 = dynamic_cast<Ball*>(rb2)) {
            collisionInfo = TestBallsCollision(ball1, ball2);
        } else if (auto* poly2 = dynamic_cast<Polygon*>(rb2)) {
            collisionInfo = TestBallPolygonCollision(ball1, poly2);
            collisionInfo.normal = - collisionInfo.normal;
        }
    } else if (auto* poly1 = dynamic_cast<Polygon*>(rb1)) {
        if (auto* ball2 = dynamic_cast<Ball*>(rb2)) {
            collisionInfo = TestBallPolygonCollision(ball2, poly1);
        } else if (auto* poly2 = dynamic_cast<Polygon*>(rb2)) {
            collisionInfo = TestPolygonsCollision(poly1, poly2);
        }
    }

    return collisionInfo;
}

CollisionInfo Collisioner::TestBallsCollision(const Ball* ball1, const Ball* ball2) {
    Vector2 distance = ball1->GetPosition() - ball2->GetPosition();

    const float radiusSum = ball1->GetRadius() + ball2->GetRadius();

    if (distance.Length() <= radiusSum) {
        const Vector2 normal = distance / distance.Length();

        float depth = radiusSum - distance.Length();

        return CollisionInfo(true, normal, depth);
    }

    return {false, Vector2(), 0.0f};
}

CollisionInfo Collisioner::TestBallPolygonCollision(const Ball* ball, const Polygon* poly) {
    const std::vector<Vector2>& vertices = poly->GetVertices();
    const Vector2 ballPos = ball->GetPosition();
    const float ballRadius = ball->GetRadius();

    Vector2 normal(0, 0);
    float depth = std::numeric_limits<float>::infinity();

    // Vérifier la projection sur les axes des arêtes du polygone
    for (size_t i = 0; i < vertices.size(); ++i) {
        Vector2 va = vertices[i];
        Vector2 vb = vertices[(i + 1) % vertices.size()];

        Vector2 edge = vb - va;
        Vector2 axis(-edge.y, edge.x);
        axis = axis.Normalize();

        auto [minA, maxA] = projectVertices(vertices, axis);
        auto [minB, maxB] = projectCircle(ballPos, ballRadius, axis);

        if (minA >= maxB || minB >= maxA) {
            return CollisionInfo(false, Vector2(), 0.0f);  // Pas d'intersection
        }

        float axisDepth = std::min(maxB - minA, maxA - minB);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    // Vérifier l'axe basé sur le point le plus proche du polygone
    size_t cpIndex = findClosestPointOnPolygon(ballPos, vertices);
    Vector2 cp = vertices[cpIndex];

    Vector2 axis = cp - ballPos;
    axis = axis.Normalize();

    auto [minA, maxA] = projectVertices(vertices, axis);
    auto [minB, maxB] = projectCircle(ballPos, ballRadius, axis);

    if (minA >= maxB || minB >= maxA) {
        return CollisionInfo(false, Vector2(), 0.0f);
    }

    float axisDepth = std::min(maxB - minA, maxA - minB);
    if (axisDepth < depth) {
        depth = axisDepth;
        normal = axis;
    }

    // Corriger la direction de la normale pour pointer vers l'extérieur du polygone
    Vector2 direction = poly->GetPosition() - ballPos;
    if (normal.Dot(direction) < 0) {
        normal = -normal;
    }

    return CollisionInfo(true, normal, depth);
}


CollisionInfo Collisioner::TestPolygonsCollision(const Polygon* poly1, const Polygon* poly2) {
    const std::vector<Vector2>& vertices1 = poly1->GetVertices();
    const std::vector<Vector2>& vertices2 = poly2->GetVertices();

    Vector2 normal(0, 0);
    float depth = std::numeric_limits<float>::infinity();

    // Vérifier la projection sur les axes des arêtes des deux polygones
    for (size_t i = 0; i < vertices1.size(); ++i) {
        Vector2 va = vertices1[i];
        Vector2 vb = vertices1[(i + 1) % vertices1.size()];
        Vector2 edge = vb - va;
        Vector2 axis(-edge.y, edge.x);
        axis = axis.Normalize();

        // Projection des vertices des deux polygones sur l'axe
        auto [minA1, maxA1] = projectVertices(vertices1, axis);
        auto [minB1, maxB1] = projectVertices(vertices2, axis);

        // Si les projections ne se chevauchent, il n'y a pas de collision
        if (maxA1 < minB1 || maxB1 < minA1) {
            return CollisionInfo(false, Vector2(), 0.0f);
        }

        // Calculer la profondeur de pénétration et la normale
        float axisDepth = std::min(maxB1 - minA1, maxA1 - minB1);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    for (size_t i = 0; i < vertices2.size(); ++i) {
        Vector2 va = vertices2[i];
        Vector2 vb = vertices2[(i + 1) % vertices2.size()];
        Vector2 edge = vb - va;
        Vector2 axis(-edge.y, edge.x);
        axis = axis.Normalize();

        // Projection des vertices des deux polygones sur l'axe
        auto [minA2, maxA2] = projectVertices(vertices1, axis);
        auto [minB2, maxB2] = projectVertices(vertices2, axis);

        // Si les projections ne se chevauchent pas, il n'y a pas de collision
        if (maxA2 < minB2 || maxB2 < minA2) {
            return CollisionInfo(false, Vector2(), 0.0f);
        }

        // Calculer la profondeur de pénétration et la normale
        float axisDepth = std::min(maxB2 - minA2, maxA2 - minB2);
        if (axisDepth < depth) {
            depth = axisDepth;
            normal = axis;
        }
    }

    return CollisionInfo(true, normal, depth);
}


std::pair<float, float> Collisioner::projectVertices(const std::vector<Vector2>& vertices, const Vector2& axis) {
    float minProj = std::numeric_limits<float>::infinity();
    float maxProj = -std::numeric_limits<float>::infinity();

    for (const Vector2& v : vertices) {
        const float proj = v.Dot(axis);
        if (proj < minProj) minProj = proj;
        if (proj > maxProj) maxProj = proj;
    }

    return {minProj, maxProj};
}

std::pair<float, float> Collisioner::projectCircle(const Vector2& center, float radius, const Vector2& axis) {
    const Vector2 direction = axis.Normalize();
    const auto directionAndRadius = Vector2(direction.x * radius, direction.y * radius);

    const Vector2 p1 = center + directionAndRadius;
    const Vector2 p2 = center - directionAndRadius;

    float minProj = p1.Dot(axis);
    float maxProj = p2.Dot(axis);

    if (minProj > maxProj) std::swap(minProj, maxProj);

    return {minProj, maxProj};
}

size_t Collisioner::findClosestPointOnPolygon(const Vector2& circleCenter, const std::vector<Vector2>& vertices) {
    size_t result = 0;
    float minDistance = std::numeric_limits<float>::infinity();

    for (size_t i = 0; i < vertices.size(); ++i) {
        const float distance = std::sqrt(std::pow(vertices[i].x - circleCenter.x, 2) +
                                   std::pow(vertices[i].y - circleCenter.y, 2));

        if (distance < minDistance) {
            minDistance = distance;
            result = i;
        }
    }

    return result;
}