#include "Game.h"
#include <iostream>
#include <random>
#include <sstream>

const float Game::INITIAL_SPEED = 0.15f; // Time between moves in seconds

Game::Game() : 
    window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Snake Game", sf::Style::Titlebar | sf::Style::Close),
    snake(GRID_WIDTH / 2, GRID_HEIGHT / 2),
    isGameOver(false),
    score(0),
    gameSpeed(INITIAL_SPEED),
    timeSinceLastMove(0.0f) {
    
    window.setFramerateLimit(60);
    
    // Try to load a font (use default if not available)
    if (!font.loadFromFile("arial.ttf")) {
        // Use default font if custom font fails to load
        std::cout << "Warning: Could not load font file. Using default font." << std::endl;
    }
    
    initializeText();
    
    // Spawn initial food
    food.spawn(getRandomFoodPosition());
}

Game::~Game() {
    // Cleanup handled automatically by SFML destructors
}

void Game::run() {
    while (window.isOpen()) {
        processEvents();
        
        if (!isGameOver) {
            update();
        }
        
        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
                
            case sf::Event::KeyPressed:
                handleInput(event.key.code);
                break;
                
            default:
                break;
        }
    }
}

void Game::handleInput(sf::Keyboard::Key key) {
    if (isGameOver) {
        if (key == sf::Keyboard::R) {
            resetGame();
        }
        return;
    }
    
    // Handle movement input
    switch (key) {
        case sf::Keyboard::Up:
        case sf::Keyboard::W:
            snake.setDirection(Direction::UP);
            break;
            
        case sf::Keyboard::Down:
        case sf::Keyboard::S:
            snake.setDirection(Direction::DOWN);
            break;
            
        case sf::Keyboard::Left:
        case sf::Keyboard::A:
            snake.setDirection(Direction::LEFT);
            break;
            
        case sf::Keyboard::Right:
        case sf::Keyboard::D:
            snake.setDirection(Direction::RIGHT);
            break;
            
        case sf::Keyboard::Escape:
            window.close();
            break;
            
        default:
            break;
    }
}

void Game::update() {
    float deltaTime = clock.restart().asSeconds();
    timeSinceLastMove += deltaTime;
    
    // Move snake based on game speed
    if (timeSinceLastMove >= gameSpeed) {
        snake.move();
        timeSinceLastMove = 0.0f;
        
        // Check for collisions
        if (checkCollisions()) {
            gameOver();
            return;
        }
        
        // Check if food is eaten
        if (food.isEaten(snake.getHeadPosition())) {
            snake.grow();
            score += 10;
            updateScore();
            increaseDifficulty();
            
            // Spawn new food
            food.spawn(getRandomFoodPosition());
        }
    }
}

void Game::render() {
    window.clear(sf::Color::Black);
    
    // Render game objects
    snake.render(window, CELL_SIZE);
    food.render(window, CELL_SIZE);
    
    // Render UI
    window.draw(scoreText);
    
    if (isGameOver) {
        window.draw(gameOverText);
        window.draw(restartText);
    }
    
    window.display();
}

bool Game::checkCollisions() {
    // Check wall collision
    if (snake.checkWallCollision(GRID_WIDTH, GRID_HEIGHT)) {
        return true;
    }
    
    // Check self collision
    if (snake.checkSelfCollision()) {
        return true;
    }
    
    return false;
}

void Game::gameOver() {
    isGameOver = true;
    clock.restart(); // Reset clock to avoid time accumulation
}

void Game::resetGame() {
    isGameOver = false;
    score = 0;
    gameSpeed = INITIAL_SPEED;
    timeSinceLastMove = 0.0f;
    
    snake.reset(GRID_WIDTH / 2, GRID_HEIGHT / 2);
    food.spawn(getRandomFoodPosition());
    
    updateScore();
    clock.restart();
}

void Game::initializeText() {
    // Score text
    scoreText.setFont(font);
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(10, 10);
    
    // Game over text
    gameOverText.setFont(font);
    gameOverText.setString("GAME OVER");
    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    
    // Center the game over text
    sf::FloatRect gameOverBounds = gameOverText.getLocalBounds();
    gameOverText.setPosition(
        (WINDOW_WIDTH - gameOverBounds.width) / 2,
        (WINDOW_HEIGHT - gameOverBounds.height) / 2 - 50
    );
    
    // Restart text
    restartText.setFont(font);
    restartText.setString("Press R to Restart");
    restartText.setCharacterSize(24);
    restartText.setFillColor(sf::Color::Yellow);
    
    // Center the restart text
    sf::FloatRect restartBounds = restartText.getLocalBounds();
    restartText.setPosition(
        (WINDOW_WIDTH - restartBounds.width) / 2,
        (WINDOW_HEIGHT - restartBounds.height) / 2 + 20
    );
    
    updateScore();
}

void Game::updateScore() {
    std::ostringstream oss;
    oss << "Score: " << score;
    scoreText.setString(oss.str());
}

void Game::increaseDifficulty() {
    // Gradually increase speed as score increases
    if (score % 50 == 0 && gameSpeed > 0.05f) { // Every 5 food items
        gameSpeed *= 0.95f; // Increase speed by 5%
    }
}

sf::Vector2i Game::getRandomFoodPosition() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    
    sf::Vector2i newPos;
    std::deque<sf::Vector2i> snakeBody = snake.getBody();
    
    do {
        std::uniform_int_distribution<> xDist(0, GRID_WIDTH - 1);
        std::uniform_int_distribution<> yDist(0, GRID_HEIGHT - 1);
        
        newPos.x = xDist(gen);
        newPos.y = yDist(gen);
        
        // Make sure food doesn't spawn on snake
    } while (std::find(snakeBody.begin(), snakeBody.end(), newPos) != snakeBody.end());
    
    return newPos;
}