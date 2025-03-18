#include <random>
#include <vector>
#include <cmath>
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

    std::vector<RigidBody *> objects;
    const float radius = 8.0f;  // Rayon des balles
    const float horizontalDistance = 8.0f * radius;  // Distance horizontale entre les balles
    const float verticalDistance = std::sqrt(8.0f) * radius;  // Distance verticale entre les balles

    // Placer les balles inertes en une grille hexagonale
    const int numRows = 15;  // Nombre de lignes de balles
    const int numCols = 15;  // Nombre de colonnes de balles

    // Position centrale de la grille (au centre de l'écran)
    const float centerX = static_cast<float>(renderWindow.getSize().x) / 2;
    const float centerY = static_cast<float>(renderWindow.getSize().y) / 2;

    // Génération des balles pour la grille hexagonale
    for (int row = 0; row < numRows; ++row) {
        for (int col = 0; col < numCols; ++col) {
            // Calculer la position (x, y) pour chaque balle
            float x = centerX + (static_cast<float>(col) - static_cast<float>(numRows) / 2) * horizontalDistance;
            float y = centerY + (static_cast<float>(row) - static_cast<float>(numCols) / 2) * verticalDistance;

            // Décalage des lignes paires
            if (row % 2 == 1) {
                x += radius * 4;  // Décaler de 'radius' pour les colonnes impaires
            }

            RigidBody *obj = new Ball(Vector2(x, y), radius, radius, 0.f);  // Création d'une balle
            world.AddRigidBody(obj);
            objects.push_back(obj);
        }
    }

    // Ajout du sol et des murs
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

    // Lancer le moteur
    engine.Run();
    world.Clear();

    // Nettoyage mémoire
    for (const RigidBody *obj: objects) {
        delete obj;
    }

    return 0;
}
