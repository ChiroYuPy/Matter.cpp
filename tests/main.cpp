//
// Created by adrian on 02/04/25.
//

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
    world.setGravity({0, 98.1f});

    auto wall1 = Box({0, 0}, 800, 10);
    wall1.setInert(true);

    auto wall2 = Box({0, 0}, 10, 600);
    wall2.setInert(true);

    auto wall3 = Box({790, 0}, 10, 600);
    wall3.setInert(true);

    auto wall4 = Box({0, 590}, 800, 10);
    wall4.setInert(true);

    world.addRigidBody(&wall1);
    world.addRigidBody(&wall2);
    world.addRigidBody(&wall3);
    world.addRigidBody(&wall4);

    // Création des balles (en utilisant un vecteur de pointeurs)
    std::vector<std::unique_ptr<Ball>> balls;
    for (int i = 0; i < 256; ++i) {
        // Position aléatoire des balles
        float randomX = static_cast<float>(window.getSize().x / 2) * (-0.5f + static_cast<float>(std::rand()) / RAND_MAX);
        float randomY = static_cast<float>(window.getSize().y / 2) * (-0.5f + static_cast<float>(std::rand()) / RAND_MAX);
        Vector2f vector = {randomX, randomY};

        auto ball = std::make_unique<Ball>(vector, 0);
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
            sf::CircleShape ballShape(32);
            ballShape.setOrigin({32, 32});
            ballShape.setPosition(ball->getPosition().x, ball->getPosition().y);
            ballShape.setFillColor(sf::Color::Green);
            window.draw(ballShape);
        }

        // Dessiner les murs
        sf::RectangleShape wallShape1(sf::Vector2f(800.f, 10.f));  // Mur supérieur
        wallShape1.setPosition(wall1.getPosition().x, wall1.getPosition().y);
        wallShape1.setFillColor(sf::Color::Blue);
        window.draw(wallShape1);

        sf::RectangleShape wallShape2(sf::Vector2f(10.f, 600.f));  // Mur gauche
        wallShape2.setPosition(wall2.getPosition().x, wall2.getPosition().y);
        wallShape2.setFillColor(sf::Color::Blue);
        window.draw(wallShape2);

        sf::RectangleShape wallShape3(sf::Vector2f(10.f, 600.f));  // Mur droit
        wallShape3.setPosition(wall3.getPosition().x, wall3.getPosition().y);
        wallShape3.setFillColor(sf::Color::Blue);
        window.draw(wallShape3);

        sf::RectangleShape wallShape4(sf::Vector2f(800.f, 10.f));  // Mur inférieur
        wallShape4.setPosition(wall4.getPosition().x, wall4.getPosition().y);
        wallShape4.setFillColor(sf::Color::Blue);
        window.draw(wallShape4);

        window.display();

        std::cout << "Ball Position: " << balls[0]->getPosition().x << " " << balls[0]->getPosition().y << std::endl;

        sf::sleep(sf::milliseconds(16));
    }

    return 0;
}
