#include "Engine.h"

Engine::Engine() : window(sf::VideoMode(1280, 1280), "Physics Engine"), world(Vector2f(0, 98.1f)),
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
    sf::Event event{};
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            HandleMouseClick(sf::Mouse::getPosition(window));
        }
        if (event.type == sf::Event::MouseButtonReleased) {
            HandleMouseRelease();
        }
    }
}

void Engine::ClampPosition(RigidBody *body) const {
    Vector2 position = body->GetPosition();
    Vector2 velocity = body->GetVelocity();

    const float half_width = body->GetAABB().getWidth() / 2;
    const float half_height = body->GetAABB().getHeight() / 2;

    const float windowWidth = static_cast<float>(window.getSize().x);
    const float windowHeight = static_cast<float>(window.getSize().y);

    constexpr float bounceFactor = 1.f;

    if (position.x - half_width < 0) {
        position.x = half_width;
        velocity.x = -velocity.x * bounceFactor;
    } else if (position.x + half_width > windowWidth) {
        position.x = windowWidth - half_width;
        velocity.x = -velocity.x * bounceFactor;
    }

    if (position.y - half_height < 0) {
        position.y = half_height;
        velocity.y = -velocity.y * bounceFactor;
    } else if (position.y + half_height > windowHeight) {
        position.y = windowHeight - half_height;
        velocity.y = -velocity.y * bounceFactor;
    }

    body->SetPosition(position);
    body->SetVelocity(velocity);
}


void Engine::Update(const float dt) {
    world.Update(dt);

    if (selectedObject != nullptr) {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        selectedObject->SetPosition(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        selectedObject->SetVelocity(Vector2f(0, 0));
    }

    for (const auto body: world.GetRigidBodies()) {
        ClampPosition(body);
    }
}

void Engine::HandleMouseClick(const sf::Vector2i &mousePos) {
    for (RigidBody *rb: world.GetRigidBodies()) {
        if (AABB aabb = rb->GetAABB(); aabb.contain(Vector2(static_cast<float>(mousePos.x),
                                                            static_cast<float>(mousePos.y)))) {
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

    for (RigidBody *rb: world.GetRigidBodies()) {
        constexpr float maxSpeed = 500.0f;

        if (auto *ball = dynamic_cast<Ball *>(rb)) {
            sf::CircleShape circle(ball->GetRadius());
            circle.setPosition(ball->GetPosition().x - ball->GetRadius(),
                               ball->GetPosition().y - ball->GetRadius());

            float speed = Vector2f::Length(ball->GetVelocity());
            float ratio = std::min(speed / maxSpeed, 1.0f);

            if (!ball->IsInert()) {
                auto red = static_cast<sf::Uint8>(255 * ratio);
                auto green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
                circle.setFillColor(sf::Color(red, green, 0));
            } else {
                circle.setFillColor(sf::Color(32, 32, 32));
            }

            window.draw(circle);
        } else if (auto *poly = dynamic_cast<Polygon *>(rb)) {
            if (const std::vector<Vector2f> &vertices = poly->GetVertices(); !vertices.empty()) {
                sf::ConvexShape convex;
                convex.setPointCount(vertices.size());
                for (size_t i = 0; i < vertices.size(); ++i) {
                    convex.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
                }

                float speed = Vector2f::Length(poly->GetVelocity());
                float ratio = std::min(speed / maxSpeed, 1.0f);

                if (!poly->IsInert()) {
                    auto red = static_cast<sf::Uint8>(255 * ratio);
                    auto green = static_cast<sf::Uint8>(255 * (1.0f - ratio));
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
        auto bodyA = j->GetBodyA();
        auto bodyB = j->GetBodyB();

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
