# 🌌 Project Voidmarch

**Project Voidmarch** is an action-RTS hybrid built in **C++** using the **Raylib** engine — a fast, open-source framework for 2D game development.  
Set in a surreal, space-fueled fantasy world, Voidmarch fuses **real-time combat**, **scaling-based progression**, and **tactical positioning** into a single cohesive gameplay experience.

---

## 🎮 Game Overview

**Genre:** 2D Action / Strategy Hybrid  
**Engine:** Raylib (C++)  
**Languages:** C++17 / Rust (for math and performance-critical modules)  
**Platforms:** Windows (MSYS2 + MinGW64), Linux (most should work)  

In Voidmarch, players command unique races with distinct playstyles, weapons, and abilities — navigating intricate arenas, striking with precision, and evolving their strength through a dynamic scaling system.

### ✦ Playable Races
- **Voidcrawler** – fast, shadow-based attacks and teleport mobility  
- **Spacelizard** – hybrid of melee and plasma weaponry  
- **Mecha-Sapien** – heavy gunner with modular upgrades  
- **Human** – balanced stats and access to diverse weapon classes  

### ✦ Combat & Progression
- Real-time combat based on weapon type and profession  
- Melee and ranged weapon systems (swords, blasters, projectiles)  
- Damage scaling and level-wide pixel-scale consistency via `ScaleSystem`  
- Procedural enemy behaviors and sector collision detection (`sector_hit.hpp`)  

---

## 🧠 Technical Overview

Voidmarch emphasizes **modularity** and **clean separation of logic**, ensuring maintainability and easy expansion.

### 🔩 Core Systems
| System | Description |
|--------|--------------|
| **ScaleSystem** | Handles resolution-independent pixel scaling across devices. |
| **PlayerTexManager** | Singleton managing race and profession texture sets. |
| **Weapon Abstraction** | Unified melee/ranged interface for attack logic. |
| **UI Manager** | Modular UI system with dynamic buttons and state transitions. |
| **Math Core (Rust)** | Optimized math module written in Rust and linked via FFI. |

### 📁 Folder Structure
```
project_voidMarch/
│
├── CMakeLists.txt
├── game_index/ # Main entry point and state management
├── game_logic/ # Combat, AI, and gameplay logic
├── screen_logic/ # Menu, level select, and HUD screens
├── include/ # Global headers and constants
├── math_core/ # Rust-integrated math modules
├── assets/ # Art, sound, textures (LFS-tracked)
└── build-windows/ # Build output directory
```
---
## ⚙️ How to Run
### ***!MAKE SURE YOU ARE IN THE PROJECT DIRECTORY!***

```bash
cd path/to/project
``` 
such as 
```bash
cd project_voidMarch
```


### **Option 1 (_recommended_):**
### Run the build script:
```bash
./build.sh
```

### **Option 2 (_manual_):**
### 🧹 Clear Build directory
```bash
rm -rf build
```
### 🛠️ Build the binary with CMake
```bash
cmake -B build -G Ninja
cmake --build build
```

### **Finally run the executable (After Option 1 or 2):**
Windows:
```bash
./build/void_march.exe
```
Linux:
```bash
./build/void_march
```
Enjoy!
