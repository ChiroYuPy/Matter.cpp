# 🏗 Matter.cpp – 2D Physics Engine in C++

## 🚀 Description

**Matter.cpp** is a **C++23** 2D physics engine for real-time simulation of **rigid polygonal bodies**. It supports collision handling, rotation, and forces to create dynamic and precise physics simulations.

### 🔥 Key Features

- **Rigid bodies**: Supports polygons (boxes, custom shapes, etc.).
- **Force-based physics engine**: Velocity, acceleration, gravity.
- **Collision & AABB**: Bounding box collision detection and handling.
- **Rotation & transformation**: Angle and movement management.
- **SFML support** (optional) for graphical rendering.

---

## 📥 Installation

### 🔷 Requirements

- **C++23**
- **CMake** (for compilation)
- **SFML** *(optional, for graphical rendering)*

### 📦 Clone and Compile

```bash
git clone https://github.com/ChiroYuPy/Matter.cpp.git
cd Matter.cpp
mkdir build && cd build
cmake ..
make
```

---

## 🎮 Usage

### 🏗 Example: Creating a Polygon

The following code creates a polygon and retrieves its AABB (axis-aligned bounding box) after transformation:

```cpp
#include "MATTER/objects/Polygon.h"

int main() {
    std::vector<Vector2f> vertices = {
        { -50, -50 }, { 50, -50 }, { 50, 50 }, { -50, 50 }
    };
    
    Polygon polygon({100, 100}, vertices);
    polygon.update(1.0f / 60.0f); // Physics update
    
    AABB bounds = polygon.getAABB();
    std::cout << "AABB Min: (" << bounds.min.x << ", " << bounds.min.y << ")\n";
    std::cout << "AABB Max: (" << bounds.max.x << ", " << bounds.max.y << ")\n";
    
    return 0;
}
```

### 🔄 Example: Dynamic Updates

```cpp
polygon.applyForce(Vector2f(10.0f, -5.0f)); // Apply force
polygon.update(1.0f / 60.0f); // Physics update
```

---

## 📌 Examples & Demos

- **Box & Polygon**: Collision simulation between rigid shapes.
- **Transformation**: Polygon rotation and scaling.

---

## 🤝 Contribution

Want to improve **Matter.cpp**? Contributions are welcome! 🚀

1. **Fork** the project
2. Create a **branch** (`git checkout -b feature/improvement`)
3. **Commit** your changes (`git commit -am "Fix Polygon transformation"`)
4. **Push** to your repo (`git push origin feature/improvement`)
5. Submit a **Pull Request**

---

## 📝 License

This project is under the MIT License. See the [LICENSE](LICENSE) file for more details.

🔗 **Author**: [ChiroYuPy](https://github.com/ChiroYuPy)  
⭐ **If you like this project, don't forget to leave a star!**

