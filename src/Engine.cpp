#include "Engine.h"
#include <iostream>

Engine::Engine() : window(sf::VideoMode(1280, 1280), "Physics Engine"), world(Vector2(0, 98.1f)),
                   selectedObject(nullptr) {
}

void Engine::Run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();
        ProcessEvents();
        Update(dt);
        Render();
    }
}

World &Engine::GetWorld() {
    return world;
}

sf::RenderWindow &Engine::GetWindow() {
    return window;
}

void Engine::ProcessEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            // Si la souris clique, gérer l'événement
            HandleMouseClick(sf::Mouse::getPosition(window));
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            // Si la souris relâche le bouton, arrêter de déplacer l'objet
            HandleMouseRelease();
        }
    }
}

void Engine::ClampPosition(RigidBody *body) {
    Vector2 position = body->GetPosition();
    Vector2 velocity = body->GetVelocity();
    float half_width = body->GetAABB().GetWidth() / 2;
    float half_height = body->GetAABB().GetHeight() / 2;

    // Coefficient de restitution (contrôle la perte d'énergie lors des rebonds)
    const float bounceFactor = 1.f; // Ajustez entre 0 (pas de rebond) et 1 (rebond parfait)

    // Limiter la position en X
    if (position.x - half_width < 0) {
        position.x = half_width; // Replacer à la limite gauche
        velocity.x = -velocity.x * bounceFactor; // Inverser la vitesse avec restitution
    } else if (position.x + half_width > window.getSize().x) {
        position.x = window.getSize().x - half_width; // Replacer à la limite droite
        velocity.x = -velocity.x * bounceFactor;
    }

    // Limiter la position en Y
    if (position.y - half_height < 0) {
        position.y = half_height; // Replacer à la limite supérieure
        velocity.y = -velocity.y * bounceFactor;
    } else if (position.y + half_height > window.getSize().y) {
        position.y = window.getSize().y - half_height; // Replacer à la limite inférieure
        velocity.y = -velocity.y * bounceFactor;
    }

    // Appliquer les corrections
    body->SetPosition(position);
    body->SetVelocity(velocity);
}


void Engine::Update(float dt) {
    world.Update(dt);

    // Déplacer l'objet sélectionné avec la souris
    if (selectedObject != nullptr) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        selectedObject->SetPosition(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        selectedObject->SetVelocity(Vector2(0, 0));
    }

    for (auto body: world.GetRigidBodies()) {
        ClampPosition(body);
    }
}

void Engine::HandleMouseClick(const sf::Vector2i &mousePos) {
    for (RigidBody *rb: world.GetRigidBodies()) {
        AABB aabb = rb->GetAABB();
        if (aabb.Contain(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))) {
            selectedObject = rb;
            break;
        }
    }
}

void Engine::HandleMouseRelease() {
    if (selectedObject != nullptr) {
    }
    selectedObject = nullptr;
}

void Engine::Render() {
    window.clear(sf::Color::Black);

    const float maxSpeed = 500.0f;

    // Itération sur tous les corps rigides
    for (RigidBody *rb: world.GetRigidBodies()) {
        // Si c'est une balle, on la dessine comme un cercle
        if (auto *ball = dynamic_cast<Ball *>(rb)) {
            sf::CircleShape circle(ball->GetRadius());
            circle.setPosition(ball->GetPosition().x - ball->GetRadius(),
                               ball->GetPosition().y - ball->GetRadius());

            float speed = ball->GetVelocity().Length();
            float ratio = std::min(speed / maxSpeed, 1.0f);

            if (!ball->IsInert()) {
                sf::Uint8 red = static_cast<sf::Uint8>(255 * ratio);
                sf::Uint8 green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
                circle.setFillColor(sf::Color(red, green, 0));
            } else {
                circle.setFillColor(sf::Color(32, 32, 32));
            }

            window.draw(circle);
        }
        // Sinon, si c'est un polygone, on le dessine via ses sommets
        else if (auto *poly = dynamic_cast<Polygon *>(rb)) {
            const std::vector<Vector2>& vertices = poly->GetVertices();
            if (!vertices.empty()) {
                sf::ConvexShape convex;
                convex.setPointCount(vertices.size());
                for (size_t i = 0; i < vertices.size(); ++i) {
                    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
                }

                float speed = poly->GetVelocity().Length();
                float ratio = std::min(speed / maxSpeed, 1.0f);

                if (!poly->IsInert()) {
                    sf::Uint8 red = static_cast<sf::Uint8>(255 * ratio);
                    sf::Uint8 green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
                    convex.setFillColor(sf::Color(red, green, 0));
                } else {
                    convex.setFillColor(sf::Color(32, 32, 32));
                }
                window.draw(convex);
            }
        }
    }

    // Dessiner les joints (lignes entre les objets liés)
    for (Join *j: world.GetJoins()) {
        Particle *bodyA = j->GetBodyA();
        Particle *bodyB = j->GetBodyB();

        if (bodyA && bodyB) {
            Vector2 posA = bodyA->GetPosition();
            Vector2 posB = bodyB->GetPosition();

            sf::VertexArray line(sf::Lines, 2);
            line[0].position = sf::Vector2f(posA.x, posA.y);
            line[1].position = sf::Vector2f(posB.x, posB.y);

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            window.draw(line);
        }
    }

    window.display();
}
