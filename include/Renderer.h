//
// Created by adrian on 25/02/25.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "Physics/World.h"

class Renderer {
    Renderer();
public:
    static void render(sf::RenderWindow &renderWindow, World &world);
};
