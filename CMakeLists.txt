# This CMakeLists file is used by the test project to use the Matter library.

cmake_minimum_required(VERSION 3.16)
project(MatterTest VERSION 1.0.0)

# Optionally find and link SFML (uncomment if needed)
# find_package(SFML 2.5 REQUIRED graphics window system)

# Add the Matter library as a subdirectory (used for compiling the library)
add_subdirectory(MatterLib) # Do not copy this line when using the library

# Define the executable for the test application
add_executable(main tests/main.cpp)

# Link the Matter library and SFML libraries (uncomment SFML lines if using SFML)
target_link_libraries(main PRIVATE Matter sfml-graphics sfml-window sfml-system)
