cmake_minimum_required(VERSION 3.16)
project(MatterTest)

# find_package(SFML 2.5 REQUIRED graphics window system)

add_subdirectory(MatterLib) # just for compiling, if you use the library, do not copy that

add_executable(app tests/main.cpp)
target_link_libraries(app PRIVATE Matter sfml-graphics sfml-window sfml-system)
