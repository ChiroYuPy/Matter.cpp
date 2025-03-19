#include "Renderer.h"

void Renderer::render(sf::RenderWindow &renderWindow, World &world) {
    renderWindow.clear(sf::Color::Black);

    for (RigidBody *rb: world.GetRigidBodies()) {
        constexpr float maxSpeed = 500.0f;

        if (auto *ball = dynamic_cast<Ball *>(rb)) {
            sf::CircleShape circle(ball->GetRadius());
            circle.setPosition(ball->getPosition().x - ball->GetRadius(),
                               ball->getPosition().y - ball->GetRadius());

            float speed = Vector2f::Length(ball->getVelocity());
            float ratio = std::min(speed / maxSpeed, 1.0f);

            if (!ball->isInert()) {
                auto red = static_cast<sf::Uint8>(255 * ratio);
                auto green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
                circle.setFillColor(sf::Color(red, green, 0));
            } else {
                circle.setFillColor(sf::Color(32, 32, 32));
            }

            renderWindow.draw(circle);
        } else if (auto *poly = dynamic_cast<Polygon *>(rb)) {
            if (const std::vector<Vector2f> &vertices = poly->getVertices(); !vertices.empty()) {
                sf::ConvexShape convex;
                convex.setPointCount(vertices.size());
                for (size_t i = 0; i < vertices.size(); ++i) {
                    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
                }

                float speed = Vector2f::Length(poly->getVelocity());
                float ratio = std::min(speed / maxSpeed, 1.0f);

                if (!poly->isInert()) {
                    auto red = static_cast<sf::Uint8>(255 * ratio);
                    auto green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
                    convex.setFillColor(sf::Color(red, green, 0));
                } else {
                    convex.setFillColor(sf::Color(32, 32, 32));
                }
                renderWindow.draw(convex);
            }
        }
    }

    // Dessiner les joints (lignes entre les objets liés)
    for (Join *j: world.GetJoins()) {
        auto bodyA = j->GetBodyA();
        auto bodyB = j->GetBodyB();

        if (bodyA && bodyB) {
            Vector2 posA = bodyA->getPosition();
            Vector2 posB = bodyB->getPosition();

            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(posA.x, posA.y);
            line[1].position = sf::Vector2f(posB.x, posB.y);

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            renderWindow.draw(line);
        }
    }

    renderWindow.display();
}
