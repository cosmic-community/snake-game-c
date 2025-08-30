# Snake Game C++

A classic and addictive Snake game implementation in C++ using the SFML graphics library. Control a growing snake, collect food, avoid collisions, and chase high scores in this timeless arcade game.

![Game Preview](https://images.unsplash.com/photo-1511512578047-dfb367046420?w=1200&h=300&fit=crop&auto=format)

## Features

- **Classic Gameplay**: Traditional snake mechanics with modern smooth controls
- **Progressive Difficulty**: Game speed increases as your snake grows longer
- **Score System**: Track your current score and compete for high scores
- **Collision Detection**: Accurate wall and self-collision detection
- **Visual Effects**: Smooth animations and visual feedback
- **Game Over Handling**: Restart functionality to keep playing
- **Cross-Platform**: Works on Windows, macOS, and Linux with SFML

<!-- CLONE_PROJECT_BUTTON -->

## Prompts

This application was built using the following prompts to generate the content structure and code:

### Content Model Prompt

> No content model prompt provided - app built as a standalone C++ game application

### Code Generation Prompt

> create a video game using c++. Keep it simple but very addicting

The app has been tailored to provide an engaging and addictive gaming experience with classic Snake gameplay mechanics.

## Technologies Used

- **C++17**: Modern C++ with standard library features
- **SFML 2.6**: Simple and Fast Multimedia Library for graphics, input, and window management
- **CMake**: Cross-platform build system for easy compilation
- **Standard Library**: Vector containers and random number generation

## Getting Started

### Prerequisites

- **C++ Compiler**: GCC 7+ / Clang 5+ / MSVC 2017+ with C++17 support
- **CMake**: Version 3.10 or higher
- **SFML 2.6**: Graphics and multimedia library

### Installation

#### Option 1: Using Package Managers

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install build-essential cmake libsfml-dev
```

**macOS (with Homebrew):**
```bash
brew install cmake sfml
```

**Windows (with vcpkg):**
```bash
vcpkg install sfml:x64-windows
```

#### Option 2: Build SFML from Source

1. Download SFML 2.6 from [https://www.sfml-dev.org/download.php](https://www.sfml-dev.org/download.php)
2. Extract and build according to SFML documentation
3. Set `SFML_ROOT` environment variable to SFML installation path

### Building the Game

1. **Clone and navigate to project:**
```bash
git clone <your-repo-url>
cd snake-game-cpp
```

2. **Create build directory:**
```bash
mkdir build
cd build
```

3. **Configure with CMake:**
```bash
cmake ..
# Or specify SFML path if needed:
# cmake -DSFML_ROOT=/path/to/sfml ..
```

4. **Build the project:**
```bash
cmake --build .
# Or with specific configuration:
# cmake --build . --config Release
```

5. **Run the game:**
```bash
./SnakeGame
# On Windows:
# ./SnakeGame.exe
```

### Controls

- **Arrow Keys**: Move snake (Up, Down, Left, Right)
- **WASD**: Alternative movement controls
- **R**: Restart game after game over
- **Escape**: Close the game

### Game Mechanics

- **Objective**: Control the snake to eat food and grow as long as possible
- **Growth**: Each food item makes the snake longer and increases your score
- **Speed**: Game speed gradually increases as your snake grows
- **Collision**: Game ends if snake hits walls or its own body
- **Scoring**: 10 points per food item collected

## Game Features Explained

### Snake Movement
The snake moves continuously in its current direction. Players can change direction using arrow keys or WASD, but cannot reverse directly into the snake's body.

### Food System
Food appears randomly on the grid at locations not occupied by the snake. When consumed, it disappears and a new food item spawns elsewhere.

### Collision Detection
The game checks for two types of collisions:
- **Wall Collision**: Snake head hits the window boundaries
- **Self Collision**: Snake head touches any part of its own body

### Difficulty Progression
As your score increases, the game speed gradually increases, making it more challenging to control the snake and avoid collisions.

## Customization

You can easily modify game parameters in the source code:

- **Grid Size**: Adjust `GRID_WIDTH` and `GRID_HEIGHT` in `Game.h`
- **Window Size**: Modify `WINDOW_WIDTH` and `WINDOW_HEIGHT`
- **Initial Speed**: Change `INITIAL_SPEED` for different starting difficulty
- **Speed Increase**: Adjust speed progression in the update logic
- **Colors**: Modify RGB values in the rendering functions

## Deployment Options

### Standalone Executable
Build a release version and distribute the executable along with required SFML libraries.

### Package Distribution
- **Windows**: Create installer with dependencies using NSIS or Inno Setup
- **macOS**: Create .app bundle with frameworks
- **Linux**: Create AppImage or distribute via package managers

### Static Linking
Link SFML statically to create a self-contained executable:
```bash
cmake -DSFML_STATIC_LIBRARIES=TRUE ..
```
