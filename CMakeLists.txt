cmake_minimum_required(VERSION 3.30)
project(untitled2)

set(CMAKE_CXX_STANDARD 20)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(untitled2
        main.cpp
        src/World.cpp
        src/Particle.cpp
)

target_link_libraries(untitled2 sfml-graphics sfml-window sfml-system)