cmake_minimum_required(VERSION 3.16)
project(Matter)

add_library(Matter STATIC

        src/math/Vector2.cpp
        src/math/AABB.cpp

        src/objects/Particle.cpp
        src/objects/RigidBody.cpp
        src/objects/Ball.cpp
        src/objects/Polygon.cpp
        src/objects/Box.cpp
        src/objects/Join.cpp

        src/Collisioner.cpp
        src/Solver.cpp
        src/World.cpp
)
target_include_directories(Matter PUBLIC include)
