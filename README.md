# Algorithmic Chess Engine ♟️

![C++](https://img.shields.io/badge/C++14-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![SFML](https://img.shields.io/badge/SFML_3.0-8CC445?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)

A high-performance, object-oriented chess simulator built in C++. Unlike traditional procedural implementations, this engine functions as a self-aware state machine. It utilizes SFML for hardware-accelerated 2D rendering, decoupling the graphical frontend from the rigorous mathematical backend. 

The engine actively enforces physical chess rules, calculates polymorphic piece constraints, and executes in-memory move simulations to prevent illegal board states.

> **Note:** Insert a high-res GIF or screenshot of your gameplay here.
> `![Gameplay Demo](docs/assets/demo.gif)`

---

## 🔥 Core Engine Features

* **Algorithmic Move Simulation:** Implements a real-time "Radar" system. Before committing a move, the engine temporarily alters pointer states and runs an $O(N^2)$ threat scan across the grid to detect absolute pins. If the King is mathematically endangered, the memory is instantly rolled back.
* **Polymorphic Dispatch:** The central board manager uses dynamic binding (`grid[row][col]->isValidMove()`) to route physics calculations to concrete piece classes (`Knight`, `Queen`, etc.) without rigid, hardcoded type checking.
* **Strict Memory Management:** Utilizes a dynamic 2D pointer array. Piece capture and promotion triggers strict heap reallocation (`delete` and `new`) to prevent memory leaks during prolonged execution.
* **Automated Endgame Evaluation:** Brute-force algorithmic scanning detects Checkmate and Stalemate conditions when zero legally viable moves remain for the active player.
* **Advanced Mechanics:** Full support for Castling (with transit-square validation) and Pawn Promotion.

---

## 🏗️ System Architecture

The architecture relies on a modified **Model-View-Controller (MVC)** pattern combined with a strict **Finite State Machine (FSM)**:
1. **Model:** The `Board` class and `Piece` hierarchy hold the definitive 8x8 memory state. Completely blind to the UI.
2. **View:** The SFML rendering loop operates at 60 FPS, translating 2D mathematical array indices into pixel coordinates.
3. **Controller:** Handles hardware interrupts (mouse clicks) via a 2-step FSM (State 0: Selection $\rightarrow$ State 1: Resolution) to prevent invalid memory access.

---

## ⚙️ Build and Execution (Linux)

This engine is designed to be compiled natively on Linux using `g++`. 

### 1. Install Dependencies (SFML)
Ensure you have the SFML development libraries installed.

**For Arch / CachyOS:**
```bash
sudo pacman -S sfml
