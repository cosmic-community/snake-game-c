#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "Snake.h"
#include "Food.h"

class Game {
public:
    Game();
    ~Game();
    
    void run();

private:
    void processEvents();
    void update();
    void render();
    void handleInput(sf::Keyboard::Key key);
    void resetGame();
    void gameOver();
    
    // Game constants
    static const int WINDOW_WIDTH = 800;
    static const int WINDOW_HEIGHT = 600;
    static const int GRID_WIDTH = 40;
    static const int GRID_HEIGHT = 30;
    static const int CELL_SIZE = 20;
    static const float INITIAL_SPEED;
    
    // SFML objects
    sf::RenderWindow window;
    sf::Clock clock;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;
    sf::Text restartText;
    
    // Game objects
    Snake snake;
    Food food;
    
    // Game state
    bool isGameOver;
    int score;
    float gameSpeed;
    float timeSinceLastMove;
    
    // Helper methods
    void initializeText();
    void updateScore();
    void increaseDifficulty();
    bool checkCollisions();
    sf::Vector2i getRandomFoodPosition();
};

#endif // GAME_H