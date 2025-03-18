//
// Created by adrian on 25/02/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Physics/World.h"

class Engine {
public:
    Engine();

    void Run();

    World &GetWorld();

    sf::RenderWindow &GetWindow();

private:
    sf::RenderWindow window;
    World world;
    RigidBody* selectedObject;

    void ProcessEvents();

    void ClampPosition(RigidBody *body) const;

    void Update(float dt);

    void Render();

    void HandleMouseClick(const sf::Vector2i &mousePos);

    void HandleMouseRelease();
};
