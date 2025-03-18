# 🏗 Matter.cpp – Moteur Physique 2D en C++

## 🚀 Description

**Matter.cpp** est un moteur physique 2D en **C++** permettant de simuler des corps rigides et des **softbodies** en temps réel. Il gère les collisions, la friction, la rotation et les forces avec une approche optimisée pour des simulations interactives et fluides.

### 🔥 Fonctionnalités principales
- **Corps rigides** : boîtes, cercles, polygones
- **Rotation et friction** : interactions réalistes
- **Collisions et restitution** : détection et réponse physique
- **Softbodies** : objets déformables avec particules et contraintes
- **Simulation en temps réel** : optimisée pour les jeux et applications
- **Support SFML** (optionnel) pour le rendu graphique

---

## 📥 Installation

### 🔷 Prérequis
- **C++17 ou supérieur**
- **CMake** (pour la compilation)
- **SFML** *(optionnel, pour l'affichage graphique)*

### 📦 Cloner et compiler
```bash
git clone https://github.com/ChiroYuPy/Matter.cpp.git
cd Matter.cpp
mkdir build && cd build
cmake ..
make
```

---

## 🎮 Utilisation

### 🏗 Exemple de simulation de corps rigides
Le code ci-dessous crée un **monde physique** avec une boîte et une balle, et les simule à **60 FPS**.

```cpp
#include "Matter.h"

int main() {
    Matter::World world;

    // Création d'une boîte et d'une balle
    auto box = world.createRigidBody(Shape::Box, 200, 100, 50, 50, 1); // shape, x, y, width, height, mass
    auto ball = world.createRigidBody(Shape::Circle, 250, 200, 20, 1); // shape, x, y, radius, ùass

    boolean running = true;
    while (running) {
        world.update(1.0 / 60.0);  // 60 FPS
        // rendering
    }

    return 0;
}
```

### 🔗 Exemple de simulation de **softbody** avec particules et contraintes
```cpp
#include "Matter.h"

int main() {
    Matter::World world;

    // Création d'un softbody composé de particules
    auto softbody = world.createSoftBody(300, 300, 5, 5, 10, mass); // x, y, rows, cols, spacing, mass
    softbody->setElasticity(0.9);
    softbody->setDamping(0.1);

    boolean running = true;
    while (running) {
        world.update(1.0 / 60.0);  // 60 FPS
        // rendering
    }

    return 0;
}
```

---

## 🔧 Personnalisation et Extensions

### Modifier les propriétés d'un objet
```cpp
box->setFriction(0.5);
box->setRestitution(0.8); // Coefficient de rebond
box->setVelocity(10, -5);
```

### Ajouter une force externe
```cpp
ball->applyForce(Matter::Vector(0, -10));  // Gravitation inversée
```

### Créer une contrainte entre deux objets
```cpp
auto constraint = world.createConstraint(box, ball, 100); // Distance fixe de 100px
```

---

## 📌 Exemples et Démonstrations
- **RigidBody Demo** : Simulation de boîtes et cercles en collision
- **SoftBody Demo** : Simulation d’un tissu élastique
- **Car Physics** : Voiture avec suspension et contraintes

---

## 🤝 Contribution
Tu veux améliorer **Matter.cpp** ? Toutes les contributions sont les bienvenues ! 🚀  
1. **Fork** le projet
2. Crée une **branche** (`git checkout -b feature/amélioration`)
3. **Commit** tes modifications (`git commit -am "Ajout d'une nouvelle feature"`)
4. **Push** vers ton repo (`git push origin feature/amélioration`)
5. Fais une **Pull Request**

---

## 📝 License
Ce projet est sous la licence MIT. Consulte le fichier [LICENSE](LICENSE) pour plus d’informations.

🔗 **Auteur** : [ChiroYuPy](https://github.com/ChiroYuPy)  
⭐ **Si ce projet t’intéresse, n’hésite pas à laisser une étoile !**

![MatterCppExemple](https://github.com/user-attachments/assets/3f8bd4a1-fe9d-4e56-b544-1d485ccf6d59)
