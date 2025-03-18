#include <random>
#include <vector>
#include "Engine.h"
#include "Physics/Objects/RigidBody.h"
#include "Physics/Objects/Ball.h"
#include "Physics/Objects/Box.h"
#include "Physics/Objects/Join.h"

int main() {
    Engine engine;
    World &world = engine.GetWorld();
    const sf::RenderWindow &renderWindow = engine.GetWindow();

    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution sizeDist(16.0f, 24.0f);
    std::uniform_real_distribution xDist(64.f, static_cast<float>(renderWindow.getSize().x) - 64.f);
    std::uniform_real_distribution yDist(64.f, static_cast<float>(renderWindow.getSize().y) / 2 - 64.f);
    std::bernoulli_distribution inertDist(0.1);

    std::vector<RigidBody *> objects;

    for (int i = 0; i < std::pow(2, 8); ++i) {
        const float size = sizeDist(gen);
        const float mass = size;
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool inert = inertDist(gen);

        RigidBody *obj;
        obj = new Ball(Vector2(x, y), size, mass, 0.f);

        obj->SetInert(inert);
        world.AddRigidBody(obj);
        objects.push_back(obj);
    }

    const auto ground = new Box(Vector2f(640, 1266), 1280, 32, 12, 0.f);
    ground->SetInert(true);
    world.AddRigidBody(ground);

    const auto wallLeft = new Box(Vector2f(16, 640), 1216, 32, 12, 0.f);
    wallLeft->SetInert(true);
    wallLeft->setAngle(std::numbers::pi * 0.5);
    world.AddRigidBody(wallLeft);

    const auto wallRight = new Box(Vector2f(1266, 640), 1216, 32, 12, 0.f);
    wallRight->SetInert(true);
    wallRight->setAngle(std::numbers::pi * 0.5);
    world.AddRigidBody(wallRight);

    const auto ceilling = new Box(Vector2f(640, 16), 1280, 32, 12, 0.f);
    ceilling->SetInert(true);
    world.AddRigidBody(ceilling);

    engine.Run();
    world.Clear();

    for (const RigidBody *obj: objects) {
        delete obj;
    }

    return 0;
}
