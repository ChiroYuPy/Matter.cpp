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

    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, WINDOW_SIZE - 14), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(16, WINDOW_SIZE / 2), WALL_THICKNESS, WINDOW_SIZE - 64, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE - 16, WINDOW_SIZE / 2), WALL_THICKNESS, WINDOW_SIZE - 64, 12, 0.f));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, 16), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f));

    for (auto &wall : walls) {
        wall->setInert(true);
        world.AddRigidBody(wall.release());
    }
}

void createSlopeBox(World &world, int numSlopes) {
    for (int i = 0; i < numSlopes; ++i) {
        auto slope = std::make_unique<Box>(Vector2f(WINDOW_SIZE / 2, 12), WINDOW_SIZE, WALL_THICKNESS, 12, 0.f);
        slope->setInert(true);
        world.AddRigidBody(slope.release());
    }
}

void createAppObjects(World &world, const sf::RenderWindow &renderWindow) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<float> sizeDist(16.0f, 24.0f);
    std::uniform_real_distribution<float> xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution<float> yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    createWindowBox(world);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        float size = sizeDist(gen);
        float mass = size * OBJECT_MASS_FACTOR;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool isInert = inertDist(gen);

        auto obj = std::make_unique<Ball>(Vector2(x, y), size, mass, 0.f);
        obj->setInert(isInert);
        world.AddRigidBody(obj.release());
    }
}

RigidBody *selectedObject = nullptr;
World world;
sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Physics Engine");

void HandleMouseClick(const sf::Vector2i &mousePos) {
    Vector2 mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

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

void handleEvent() {
    sf::Event event{};
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::MouseButtonPressed:
                HandleMouseClick(sf::Mouse::getPosition(window));
                break;
            case sf::Event::MouseButtonReleased:
                HandleMouseRelease();
                break;
            default:
                break;
        }
    }
}

void update(const float dt) {
    world.Update(dt);

    if (selectedObject) {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        selectedObject->setPosition(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        selectedObject->setVelocity(Vector2f(0, 0));
    }
}

void render() {
    window.clear();
    Renderer::render(window, world);
    window.display();
}

int main() {
    sf::Clock clock;
    createAppObjects(world, window);

    while (window.isOpen()) {
        const float dt = clock.restart().asSeconds();
        handleEvent();
        update(dt);
        render();
    }

    world.Clear();
    return 0;
}