#include "Renderer.h"

// Fonction pour calculer la couleur en fonction de la vitesse
sf::Color calculateColor(float const speed, float const maxSpeed, const bool isInert) {
    if (isInert) {
        return {32, 32, 32};  // Gris pour les objets inertes
    }

    const float ratio = std::min(speed / maxSpeed, 1.0f);
    const auto red = static_cast<sf::Uint8>(255 * ratio);
    const auto green = static_cast<sf::Uint8>(255 * (1.0f - ratio));

    return {red, green, 0};  // Dégradé de rouge à vert
}

// Fonction pour dessiner une forme générique, qu'elle soit un cercle ou un polygone
template <typename ShapeType>
void drawShape(sf::RenderWindow &window, const ShapeType &shape, const sf::Color &color) {
    auto shapeCopy = shape; // Crée une copie de la forme pour pouvoir la modifier
    shapeCopy.setFillColor(color);
    window.draw(shapeCopy);
}

void Renderer::render(sf::RenderWindow &renderWindow, World &world) {
    // Dessiner les objets rigides
    for (RigidBody *rb : world.GetRigidBodies()) {
        constexpr float maxSpeed = 500.0f;
        if (auto *ball = dynamic_cast<Ball *>(rb)) {
            sf::CircleShape circle(ball->GetRadius());
            circle.setPosition(ball->getPosition().x - ball->GetRadius(),
                               ball->getPosition().y - ball->GetRadius());

            float speed = Vector2f::Length(ball->getVelocity());
            drawShape(renderWindow, circle, calculateColor(speed, maxSpeed, ball->isInert()));

        } else if (auto *poly = dynamic_cast<Polygon *>(rb)) {
            const auto &vertices = poly->getVertices();
            if (!vertices.empty()) {
                sf::ConvexShape convex;
                convex.setPointCount(vertices.size());
                for (size_t i = 0; i < vertices.size(); ++i) {
                    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
                }

                float speed = Vector2f::Length(poly->getVelocity());
                drawShape(renderWindow, convex, calculateColor(speed, maxSpeed, poly->isInert()));
            }
        }
    }

    // Dessiner les joints (lignes entre les objets liés)
    for (Join *j : world.GetJoins()) {
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
}
