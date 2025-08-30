#include "Food.h"

Food::Food() : isActive(false) {
    initializeColors();
}

Food::~Food() {
    // Cleanup handled automatically
}

void Food::spawn(sf::Vector2i newPosition) {
    position = newPosition;
    isActive = true;
}

void Food::render(sf::RenderWindow& window, int cellSize) {
    if (!isActive) return;
    
    sf::RectangleShape foodRect(sf::Vector2f(cellSize - 4, cellSize - 4));
    foodRect.setPosition(
        position.x * cellSize + 2,
        position.y * cellSize + 2
    );
    
    foodRect.setFillColor(foodColor);
    foodRect.setOutlineThickness(1);
    foodRect.setOutlineColor(outlineColor);
    
    window.draw(foodRect);
    
    // Add a small highlight for visual appeal
    sf::RectangleShape highlight(sf::Vector2f(cellSize / 3, cellSize / 3));
    highlight.setPosition(
        position.x * cellSize + cellSize / 4,
        position.y * cellSize + cellSize / 4
    );
    highlight.setFillColor(sf::Color(255, 255, 255, 100)); // Semi-transparent white
    
    window.draw(highlight);
}

sf::Vector2i Food::getPosition() const {
    return position;
}

bool Food::isEaten(sf::Vector2i snakeHeadPos) const {
    return isActive && (position == snakeHeadPos);
}

void Food::initializeColors() {
    foodColor = sf::Color(200, 50, 50);    // Red food
    outlineColor = sf::Color(150, 25, 25); // Darker red outline
}