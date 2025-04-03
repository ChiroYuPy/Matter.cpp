#include <SFML/Graphics.hpp>
#include <MATTER/Matter.h>
#include <iostream>
#include <memory>
#include <cstdlib>  // Pour std::rand()

int main() {

    // sfml setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Physics Simulation");

    // MATTER setup
    World world;
    world.setUpdatePerSeconds(256);
    world.setMaxUpdatePerFrame(16);
    world.setGravity({0, 98.1f});

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    auto wall1 = std::make_unique<Box>(Vector2f(windowWidth / 2, 10), windowWidth, 20);
    wall1->setInert(true);

    auto wall2 = std::make_unique<Box>(Vector2f(10, windowHeight / 2), 20, windowHeight);
    wall2->setInert(true);

    auto wall3 = std::make_unique<Box>(Vector2f(windowWidth / 2, windowHeight - 10), windowWidth, 20);
    wall3->setInert(true);

    auto wall4 = std::make_unique<Box>(Vector2f(windowWidth - 10, windowHeight / 2), 20, windowHeight);
    wall4->setInert(true);

    auto dynBox1 = std::make_unique<Box>(Vector2f(windowWidth / 2, windowHeight / 2 + 100), 64, 64);
    dynBox1->setInert(false);

    auto dynBox2 = std::make_unique<Box>(Vector2f(windowWidth / 2, windowHeight / 2), 64, 64);
    dynBox2->setInert(false);
    dynBox1->setAngle(45);

    std::vector<std::unique_ptr<Box>> boxs;
    boxs.push_back(std::move(wall1));
    boxs.push_back(std::move(wall2));
    boxs.push_back(std::move(wall3));
    boxs.push_back(std::move(wall4));
    boxs.push_back(std::move(dynBox1));
    boxs.push_back(std::move(dynBox2));

    for (auto& box : boxs) {
        world.addRigidBody(box.get());
    }

    // Création des balles (en utilisant un vecteur de pointeurs)
    std::vector<std::unique_ptr<Ball>> balls;
    for (int i = 0; i < 3; ++i) {
        // Position aléatoire des balles
        float randomX = static_cast<float>(window.getSize().x) * (0.25f + static_cast<float>(std::rand() * 0.5) / RAND_MAX);
        float randomY = static_cast<float>(window.getSize().y) * (0.25f + static_cast<float>(std::rand() * 0.5) / RAND_MAX);
        Vector2f vector = {randomX, randomY};

        auto ball = std::make_unique<Ball>(vector, 16);
        ball->setPosition(vector);
        world.addRigidBody(ball.get());  // Ajout au monde
        balls.push_back(std::move(ball)); // Stockage de la balle dans le vecteur
    }

    while (window.isOpen()) {
        constexpr float dt = 0.016f;
        sf::Event event{};
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        world.update(dt);

        window.clear();

        // Dessiner les balles
        for (auto& ball : balls) {
            float radius = ball->getRadius();
            sf::CircleShape ballShape(radius);
            ballShape.setOrigin({radius, radius});
            ballShape.setPosition(ball->getPosition().x, ball->getPosition().y);
            ballShape.setFillColor(sf::Color::Green);
            window.draw(ballShape);

            // Dessiner la ligne de rotation
            float angle_deg = ball->getAngle(); // Angle en degrés
            float angle_rad = angle_deg * (3.14159265358979f / 180.0f); // Conversion en radians
            float length = radius; // La longueur de la ligne (par exemple, égale au rayon de la balle)

            // Calcul de la direction à partir de l'angle
            float line_x = ball->getPosition().x + length * cos(angle_rad);
            float line_y = ball->getPosition().y + length * sin(angle_rad);

            // Créer la ligne
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(ball->getPosition().x, ball->getPosition().y)),
                sf::Vertex(sf::Vector2f(line_x, line_y))
            };

            window.draw(line, 2, sf::Lines);
        }

        // Dessiner les boîtes
        for (auto& box : boxs) {
            // box->setAngle(box->getAngle() + dt);
            float width = box->getWidth();
            float height = box->getHeight();
            sf::RectangleShape rectangleShape(sf::Vector2f(width, height));
            rectangleShape.setOrigin({width / 2, height / 2});
            rectangleShape.setRotation(box->getAngle()); // L'angle est déjà en degrés
            rectangleShape.setPosition(box->getPosition().x, box->getPosition().y);
            rectangleShape.setFillColor(sf::Color::Blue);
            window.draw(rectangleShape);

            // Dessiner la ligne de rotation
            float angle_deg = box->getAngle(); // Angle en degrés
            float angle_rad = angle_deg * (3.14159265358979f / 180.0f); // Conversion en radians
            float length = width / 2; // La longueur de la ligne (par exemple, égale à la moitié de la largeur de la boîte)

            // Calcul de la direction à partir de l'angle
            float line_x = box->getPosition().x + length * cos(angle_rad);
            float line_y = box->getPosition().y + length * sin(angle_rad);

            // Créer la ligne
            sf::Vertex line[] = {
                sf::Vertex(sf::Vector2f(box->getPosition().x, box->getPosition().y)),
                sf::Vertex(sf::Vector2f(line_x, line_y))
            };

            window.draw(line, 2, sf::Lines);
        }


        window.display();

        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
