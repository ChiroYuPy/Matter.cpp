#include <SFML/Graphics.hpp>
#include "header/World.h"
#include <iostream>

int main() {
    sf::RenderWindow window(sf::VideoMode(1344, 1344), "Particle Simulation");
    window.setFramerateLimit(1000);

    World world(window);
    sf::Clock clock;
    sf::Font font;

    sf::Text fpsText;
    fpsText.setFont(font);
    fpsText.setCharacterSize(20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(10, 10);

    float fpsTimer = 0.0f;
    int frameCount = 0;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        world.update(dt);

        fpsTimer += dt;
        frameCount++;
        if (fpsTimer >= 1.0f) {
            fpsText.setString("FPS: " + std::to_string(frameCount));
            frameCount = 0;
            fpsTimer = 0.0f;
        }

        window.clear(sf::Color(32, 32, 32));

        for (const auto& p : world.getParticles()) {
            static sf::CircleShape shape;
            shape.setRadius(p.getRadius());
            shape.setOrigin(p.getRadius(), p.getRadius());
            shape.setPosition(p.getPosition());

            shape.setFillColor(p.isInert() ? sf::Color(24, 24, 24) : sf::Color(160, 64, 0));
            window.draw(shape);
        }

        for (const auto& c : world.getConstraints()) {
            sf::VertexArray line(sf::Lines, 2);
            line[0].position = c.getObjA().getPosition();
            line[1].position = c.getObjB().getPosition();

            line[0].color = sf::Color::White;
            line[1].color = sf::Color::White;

            window.draw(line);  // Dessiner la ligne
        }

        window.draw(fpsText);
        window.display();
    }

    return 0;
}
