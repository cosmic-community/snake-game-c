#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <deque>

enum class Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Snake {
public:
    Snake(int startX, int startY);
    ~Snake();
    
    void move();
    void grow();
    void setDirection(Direction newDirection);
    void render(sf::RenderWindow& window, int cellSize);
    void reset(int startX, int startY);
    
    // Getters
    sf::Vector2i getHeadPosition() const;
    std::deque<sf::Vector2i> getBody() const;
    Direction getCurrentDirection() const;
    int getLength() const;
    
    // Collision detection
    bool checkSelfCollision() const;
    bool checkWallCollision(int gridWidth, int gridHeight) const;

private:
    std::deque<sf::Vector2i> body;
    Direction currentDirection;
    Direction nextDirection;
    bool hasGrown;
    
    // Colors
    sf::Color headColor;
    sf::Color bodyColor;
    sf::Color outlineColor;
    
    void initializeColors();
    bool isValidDirection(Direction newDirection) const;
};

#endif // SNAKE_H