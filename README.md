# Algorithmic Chess Engine with SFML Rendering

An object-oriented C++ chess simulator featuring in-memory move validation, state-machine mechanics, and hardware-accelerated rendering. This is not a "dumb board"; it is a self-aware engine that enforces strict physical rules, calculates polymorphic piece physics, and actively prevents illegal memory states.

![Chess Engine Demo](image_placeholder.png) ## Core Architecture

* **Memory Management:** Utilizes a dynamic 2D pointer array (`Piece* grid[8][8]`) to represent the board state. Memory is strictly managed using `new` and `delete` during piece instantiation and capture to prevent heap overflow and memory leaks during prolonged execution.
* **Polymorphic Dispatch:** Inherits concrete piece logic (`King`, `Knight`, `Pawn`, etc.) from an abstract `Piece` base class. The central board manager uses dynamic binding (`grid[startRow][startCol]->isValidMove(...)`) to calculate physics without rigid, hardcoded type checking.
* **The Simulation Radar:** Before committing a move, the engine temporarily alters pointer states, runs an $O(N^2)$ threat scan across the grid to detect absolute pins or checks, and safely rolls back the memory if the King is mathematically endangered.
* **Endgame Evaluation:** Implements brute-force algorithmic scanning to detect Checkmate and Stalemate conditions when zero legally viable moves remain for the active player.

## System Modules

* **Model-View-Controller (MVC):** Achieves strict Separation of Concerns (SoC). The GUI rendering loop (View) is completely isolated from the backend mathematical pointer logic (Model).
* **Finite State Machine (FSM):** Hardware interrupts are controlled via a strict 2-state flow (State 0: Piece Selection $\rightarrow$ State 1: Target Resolution) to prevent buggy interactions and invalid memory access.

## Dependencies (Linux)

* `g++` (Compiler with C++14 or higher standard support)
* SFML 3.0.1+ (`sfml-graphics`, `sfml-window`, `sfml-system`)

## Build & Execute Instructions

**1. Install SFML via Package Manager**
For Debian/Ubuntu/Mint/Pop!_OS:
```bash
sudo apt update
sudo apt install libsfml-dev
