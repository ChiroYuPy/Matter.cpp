cmake_minimum_required(VERSION 3.10)
project(Matter_cpp CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.cpp" "tests/main.cpp")

add_executable(Matter_cpp tests/main ${SOURCES})

target_link_libraries(Matter_cpp sfml-graphics sfml-window sfml-system)