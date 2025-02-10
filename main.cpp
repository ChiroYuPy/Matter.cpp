#include <SFML/Graphics.hpp>
#include "header/World.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(1344, 1344), "Particle Simulation");
    World world(window);

    sf::Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        world.update(dt);

        window.clear();
        world.draw();
        window.display();
    }

    return 0;
}
