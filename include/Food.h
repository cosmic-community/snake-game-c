#ifndef FOOD_H
#define FOOD_H

#include <SFML/Graphics.hpp>
#include <vector>

class Food {
public:
    Food();
    ~Food();
    
    void spawn(sf::Vector2i position);
    void render(sf::RenderWindow& window, int cellSize);
    sf::Vector2i getPosition() const;
    bool isEaten(sf::Vector2i snakeHeadPos) const;

private:
    sf::Vector2i position;
    sf::Color foodColor;
    sf::Color outlineColor;
    bool isActive;
    
    void initializeColors();
};

#endif // FOOD_H