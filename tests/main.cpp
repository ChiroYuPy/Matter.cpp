#include <random>
#include <memory>
#include <Renderer.h>
#include <SFML/Graphics.hpp>

#include "Physics/Objects/RigidBody.h"
#include "Physics/Objects/Ball.h"
#include "Physics/Objects/Box.h"
#include "Physics/World.h"

constexpr float WINDOW_SIZE = 1280.0f;
constexpr float WALL_THICKNESS = 32.0f;
constexpr float OBJECT_MASS_FACTOR = 1.0f;
constexpr int NUM_OBJECTS = 256;

void createWindowBox(World &world) {
    std::vector<std::unique_ptr<Box>> walls;

    // Création des murs à l'intérieur de la fonction
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE - 14), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(16, WINDOW_SIZE / 2), WALL_THICKNESS, WINDOW_SIZE - 64, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE - 16, WINDOW_SIZE / 2), WALL_THICKNESS, WINDOW_SIZE - 64, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, 16), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f));

    // Ajout des murs au monde
    for (auto &wall : walls) {
        wall->setInert(true);
        world.addRigidBody(wall.release());
    }
}

void createSlopeBox(World &world, int numSlopes) {
    // Création et ajout des pentes à l'intérieur de la fonction
    for (int i = 0; i < numSlopes; ++i) {
        auto slope = std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, 12), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f);
        slope->setInert(true);
        world.addRigidBody(slope.release());
    }
}

void createAppObjects(World &world, const sf::RenderWindow &renderWindow) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> sizeDist(16.0f, 24.0f);
    std::uniform_real_distribution<float> xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution<float> yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    // Appel à la fonction pour créer les murs
    createWindowBox(world);

    // Création des objets Ball à l'intérieur de la fonction
    for (int i = 0; i < NUM_OBJECTS; ++i) {
        float size = sizeDist(gen);
        float mass = size * OBJECT_MASS_FACTOR;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool isInert = inertDist(gen);

        auto obj = std::make_unique<Ball>(Vector2(x, y), size, mass, 0.f);
        obj->setInert(isInert);
        world.addRigidBody(obj.release());
    }
}

RigidBody *selectedObject = nullptr;

void HandleMouseClick(const sf::Vector2i &mousePos, World& world) {
    const Vector2 mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

    // Recherche de l'objet sélectionné
    for (RigidBody *rb : world.GetRigidBodies()) {
        if (rb->getAABB().contain(mousePosF)) {
            selectedObject = rb;
            break;
        }
    }
}

void HandleMouseRelease() {
    selectedObject = nullptr;
}

void handleEvent(sf::RenderWindow& renderWindow, World& world) {
    sf::Event event{};
    while (renderWindow.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                renderWindow.close();
                break;
            case sf::Event::MouseButtonPressed:
                HandleMouseClick(sf::Mouse::getPosition(renderWindow), world);
                break;
            case sf::Event::MouseButtonReleased:
                HandleMouseRelease();
                break;
            default:
                break;
        }
    }
}

void update(const float dt, sf::RenderWindow& renderWindow, World& world) {
    world.update(dt);

    if (selectedObject) {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(renderWindow);
        selectedObject->setPosition(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        selectedObject->setVelocity(Vector2f(0, 0));
    }
}

void render(sf::RenderWindow& renderWindow, World& world) {
    renderWindow.clear();
    Renderer::render(renderWindow, world);
    renderWindow.display();
}

int main() {
    World world;
    world.setGravity({0, 9.81f});
    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Physics Engine");
    sf::Clock clock;

    renderWindow.setFramerateLimit(120);
    createAppObjects(world, renderWindow);

    while (renderWindow.isOpen()) {
        const float dt = clock.restart().asSeconds();
        std::cout << 1/dt << std::endl;
        handleEvent(renderWindow, world);
        update(dt, renderWindow, world);
        render(renderWindow, world);
    }

    world.Clear();
    return 0;
}
