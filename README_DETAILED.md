# README_DETAILED.md

# Snake Game C++ - Detailed Documentation

## Architecture Overview

This Snake game is built with a modular, object-oriented design using modern C++17 features and the SFML graphics library.

### Core Classes

#### Game Class (`Game.h/cpp`)
The main game controller that manages:
- Window creation and event handling
- Game loop (process events, update, render)
- Game state (score, speed, game over status)
- User input processing
- Collision detection coordination

#### Snake Class (`Snake.h/cpp`)
Manages the snake entity:
- Snake body represented as `std::deque<sf::Vector2i>` for efficient front/back operations
- Direction management with validation to prevent reversing
- Movement logic with smooth grid-based positioning
- Self-collision detection
- Visual rendering with distinct head and body colors

#### Food Class (`Food.h/cpp`)
Handles food mechanics:
- Random position spawning
- Collision detection with snake head
- Visual rendering with highlight effects
- Active state management

### Key Design Decisions

#### Data Structures
- **std::deque**: Used for snake body to allow efficient insertion at head and removal from tail
- **sf::Vector2i**: Grid-based positioning system for clean collision detection
- **Enum class Direction**: Type-safe direction representation

#### Game Loop
The game uses a fixed timestep approach: