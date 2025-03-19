#include <random>
#include <memory>
#include <Renderer.h>
#include <SFML/Graphics.hpp>

#include "Physics/Objects/RigidBody.h"
#include "Physics/Objects/Ball.h"
#include "Physics/Objects/Box.h"
#include "Physics/World.h"

constexpr float WINDOW_WIDTH = 1280.0f;
constexpr float WINDOW_HEIGHT = 1280.0f;
constexpr float WALL_THICKNESS = 32.0f;
constexpr int NUM_OBJECTS = 256;

void createWindowBox(World &world) {
    std::vector<std::unique_ptr<Box>> walls;

    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT), WINDOW_WIDTH, WALL_THICKNESS));
    walls.emplace_back(std::make_unique<Box>(Vector2f(0, WINDOW_HEIGHT / 2), WALL_THICKNESS, WINDOW_HEIGHT));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT / 2), WALL_THICKNESS, WINDOW_HEIGHT));
    walls.emplace_back(std::make_unique<Box>(Vector2f(WINDOW_WIDTH / 2, 0), WINDOW_WIDTH, WALL_THICKNESS));

    for (auto &wall : walls) {
        wall->setInert(true);
        world.addRigidBody(wall.release());
    }
}

void createSlopeBox(World &world, const int numSlopes) {
    for (int i = 0; i < numSlopes; ++i) {
        auto slope = std::make_unique<Box>(Vector2f(WINDOW_WIDTH / 2, 12), WINDOW_HEIGHT, WALL_THICKNESS);
        slope->setInert(true);
        world.addRigidBody(slope.release());
    }
}

void createAppObjects(World &world, const sf::RenderWindow &renderWindow) {
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution sizeDist(16.0f, 24.0f);
    std::uniform_real_distribution xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    createWindowBox(world);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        float size = sizeDist(gen);
        float mass = size;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool isInert = inertDist(gen);

        auto obj = std::make_unique<Ball>(Vector2(x, y), size);
        obj->setInert(isInert);
        world.addRigidBody(obj.release());
    }
}

RigidBody *selectedObject = nullptr;

void HandleMouseClick(const sf::Vector2i &mousePos, const World& world) {
    const Vector2 mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

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

void createBallSet(World &world, const sf::RenderWindow &renderWindow) {
    world.clear();
    createWindowBox(world);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution sizeDist(16.0f, 24.0f);
    std::uniform_real_distribution xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        float size = sizeDist(gen);
        float mass = size;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool isInert = inertDist(gen);

        auto obj = std::make_unique<Ball>(Vector2(x, y), size);
        obj->setInert(isInert);
        world.addRigidBody(obj.release());
    }
}

void createBoxSet(World &world, const sf::RenderWindow &renderWindow) {
    world.clear();
    createWindowBox(world);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution sizeDist(32.0f, 48.0f);
    std::uniform_real_distribution xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    for (int i = 0; i < NUM_OBJECTS; ++i) {
        float size = sizeDist(gen);
        float mass = size;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool isInert = inertDist(gen);

        auto obj = std::make_unique<Box>(Vector2(x, y), size, size);
        obj->setInert(isInert);
        world.addRigidBody(obj.release());
    }
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
            case sf::Event::KeyPressed:
                switch (event.key.code) {
                    case sf::Keyboard::Num1:
                        createBallSet(world, renderWindow);
                    break;
                    case sf::Keyboard::Num2:
                        createBoxSet(world, renderWindow);
                    break;
                    default:
                        break;
                }
            break;
            default:
                break;
        }
    }
}


void update(const float dt, const sf::RenderWindow& renderWindow, World& world) {
    world.update(dt);

    if (selectedObject) {
        const sf::Vector2i mousePos = sf::Mouse::getPosition(renderWindow);
        selectedObject->setPosition(Vector2(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)));
        selectedObject->setVelocity(Vector2f(0, 0));
    }
}

void render(sf::RenderWindow& renderWindow, World& world) {
    renderWindow.clear({32, 32, 32});
    Renderer::render(renderWindow, world);
    renderWindow.display();
}

int main() {
    World world;
    world.setUpdatePerSeconds(256);
    world.setMaxUpdatePerFrame(8);
    world.setGravity({0, 98.1f});
    sf::RenderWindow renderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Physics Engine");
    sf::Clock clock;

    renderWindow.setFramerateLimit(256);
    createAppObjects(world, renderWindow);

    while (renderWindow.isOpen()) {
        const float dt = clock.restart().asSeconds();
        std::cout << 1/dt << std::endl;
        handleEvent(renderWindow, world);
        update(dt, renderWindow, world);
        render(renderWindow, world);
    }

    world.clear();
    return 0;
}
