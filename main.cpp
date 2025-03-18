#include <random>
#include <vector>
#include "include/Engine.h"
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

    std::uniform_real_distribution massDist(8.0f, 16.0f);
    std::uniform_real_distribution xDist(0.0f, static_cast<float>(renderWindow.getSize().x));
    std::uniform_real_distribution yDist(0.0f, static_cast<float>(renderWindow.getSize().y) / 2);
    std::bernoulli_distribution inertDist(0.25);
    std::bernoulli_distribution shapeDist(0.5); // 50% chance d'être une balle ou un cube

    std::vector<RigidBody *> objects;

    // Génération aléatoire d'objets (balles ou cubes)
    for (int i = 0; i < 128; ++i) {
        const float mass = massDist(gen);
        const float size = mass * 2; // Rayon pour une balle, côté pour un cube
        const float x = xDist(gen);
        const float y = yDist(gen);
        const bool inert = inertDist(gen);

        RigidBody *obj;
        if (shapeDist(gen)) {
            // Créer une balle
            obj = new Ball(Vector2(x, y), size, mass, 0.f);
        } else {
            // Créer un cube
            obj = new Box(Vector2(x, y), size, size, mass, 0.f);
        }

        obj->SetInert(inert);
        world.AddRigidBody(obj);
        objects.push_back(obj);
    }

    // Création d'une corde de 11 balles reliées par 10 joints
    std::vector<Ball *> ropeBalls;
    const Vector2f startPosition(300, 100); // Position de départ de la corde
    constexpr float ballRadius = 20.f;
    constexpr float jointLength = ballRadius * 2.5f;

    for (int i = 0; i < 11; ++i) {
        constexpr float ballMass = 5.f;
        auto ball = new Ball(Vector2f(startPosition.x + static_cast<float>(i) * jointLength, startPosition.y), ballRadius, ballMass, 0.f);
        ball->SetInert(false);
        world.AddRigidBody(ball);
        ropeBalls.push_back(ball);
    }

    // Ajout des joints reliant les balles
    for (size_t i = 0; i < ropeBalls.size() - 1; ++i) {
        auto join = new Join(*ropeBalls[i], *ropeBalls[i + 1], jointLength, jointLength / 2, 1.f);
        world.AddJoin(join);
    }

    // Ajout de plateformes et objets fixes
    const auto ground = new Box(Vector2f(640, 1266), 1280, 32, 12, 0.f);
    ground->SetInert(true);
    world.AddRigidBody(ground);

    const auto dynamicBox = new Box(Vector2f(640, 640), 128, 128, 10, 0.f);
    dynamicBox->SetInert(false);
    world.AddRigidBody(dynamicBox);

    const auto floatingBall = new Ball(Vector2f(600, 500), 64, 10, 0.f);
    floatingBall->SetInert(false);
    world.AddRigidBody(floatingBall);

    // Lancer le moteur
    engine.Run();
    world.Clear();

    // Nettoyage mémoire
    for (const RigidBody *obj : objects) {
        delete obj;
    }
    for (const Ball *ball : ropeBalls) {
        delete ball;
    }

    return 0;
}
