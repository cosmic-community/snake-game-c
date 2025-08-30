#include "Snake.h"

Snake::Snake(int startX, int startY) : 
    currentDirection(Direction::RIGHT),
    nextDirection(Direction::RIGHT),
    hasGrown(false) {
    
    // Initialize snake with starting position
    body.push_back(sf::Vector2i(startX, startY));
    body.push_back(sf::Vector2i(startX - 1, startY));
    body.push_back(sf::Vector2i(startX - 2, startY));
    
    initializeColors();
}

Snake::~Snake() {
    // Cleanup handled automatically
}

void Snake::move() {
    // Update direction
    currentDirection = nextDirection;
    
    // Calculate new head position
    sf::Vector2i head = body.front();
    sf::Vector2i newHead = head;
    
    switch (currentDirection) {
        case Direction::UP:
            newHead.y--;
            break;
        case Direction::DOWN:
            newHead.y++;
            break;
        case Direction::LEFT:
            newHead.x--;
            break;
        case Direction::RIGHT:
            newHead.x++;
            break;
    }
    
    // Add new head
    body.push_front(newHead);
    
    // Remove tail if snake hasn't grown
    if (!hasGrown) {
        body.pop_back();
    } else {
        hasGrown = false; // Reset growth flag
    }
}

void Snake::grow() {
    hasGrown = true;
}

void Snake::setDirection(Direction newDirection) {
    if (isValidDirection(newDirection)) {
        nextDirection = newDirection;
    }
}

void Snake::render(sf::RenderWindow& window, int cellSize) {
    for (size_t i = 0; i < body.size(); ++i) {
        sf::RectangleShape segment(sf::Vector2f(cellSize - 2, cellSize - 2));
        segment.setPosition(
            body[i].x * cellSize + 1,
            body[i].y * cellSize + 1
        );
        
        if (i == 0) {
            // Head
            segment.setFillColor(headColor);
        } else {
            // Body
            segment.setFillColor(bodyColor);
        }
        
        segment.setOutlineThickness(1);
        segment.setOutlineColor(outlineColor);
        
        window.draw(segment);
    }
}

void Snake::reset(int startX, int startY) {
    body.clear();
    body.push_back(sf::Vector2i(startX, startY));
    body.push_back(sf::Vector2i(startX - 1, startY));
    body.push_back(sf::Vector2i(startX - 2, startY));
    
    currentDirection = Direction::RIGHT;
    nextDirection = Direction::RIGHT;
    hasGrown = false;
}

sf::Vector2i Snake::getHeadPosition() const {
    return body.front();
}

std::deque<sf::Vector2i> Snake::getBody() const {
    return body;
}

Direction Snake::getCurrentDirection() const {
    return currentDirection;
}

int Snake::getLength() const {
    return static_cast<int>(body.size());
}

bool Snake::checkSelfCollision() const {
    const sf::Vector2i& head = body.front();
    
    // Check if head collides with any body segment (skip head itself)
    for (size_t i = 1; i < body.size(); ++i) {
        if (head == body[i]) {
            return true;
        }
    }
    
    return false;
}

bool Snake::checkWallCollision(int gridWidth, int gridHeight) const {
    const sf::Vector2i& head = body.front();
    
    return (head.x < 0 || head.x >= gridWidth || 
            head.y < 0 || head.y >= gridHeight);
}

void Snake::initializeColors() {
    headColor = sf::Color(100, 200, 100); // Light green head
    bodyColor = sf::Color(50, 150, 50);   // Darker green body
    outlineColor = sf::Color(25, 75, 25); // Dark green outline
}

bool Snake::isValidDirection(Direction newDirection) const {
    // Prevent reversing into body
    switch (currentDirection) {
        case Direction::UP:
            return newDirection != Direction::DOWN;
        case Direction::DOWN:
            return newDirection != Direction::UP;
        case Direction::LEFT:
            return newDirection != Direction::RIGHT;
        case Direction::RIGHT:
            return newDirection != Direction::LEFT;
    }
    
    return true;
}