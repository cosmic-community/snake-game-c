class SnakeGame {
    constructor() {
        this.canvas = document.getElementById('gameCanvas');
        this.ctx = this.canvas.getContext('2d');
        this.scoreElement = document.getElementById('score');
        this.highScoreElement = document.getElementById('highScore');
        this.gameOverScreen = document.getElementById('gameOverScreen');
        this.finalScoreElement = document.getElementById('finalScore');
        this.restartBtn = document.getElementById('restartBtn');
        this.pauseBtn = document.getElementById('pauseBtn');
        
        // Game settings
        this.gridSize = 20;
        this.tileCount = this.canvas.width / this.gridSize;
        
        // Game state
        this.snake = [
            {x: 10, y: 10}
        ];
        this.food = {x: 15, y: 15};
        this.dx = 0;
        this.dy = 0;
        this.score = 0;
        this.highScore = localStorage.getItem('snakeHighScore') || 0;
        this.gameRunning = false;
        this.gamePaused = false;
        
        this.init();
    }
    
    init() {
        this.highScoreElement.textContent = this.highScore;
        this.setupEventListeners();
        this.generateFood();
        this.gameLoop();
    }
    
    setupEventListeners() {
        // Keyboard controls
        document.addEventListener('keydown', (e) => {
            if (!this.gameRunning && !this.gamePaused) {
                this.startGame();
            }
            
            switch(e.code) {
                case 'ArrowUp':
                    if (this.dy !== 1) {
                        this.dx = 0;
                        this.dy = -1;
                    }
                    break;
                case 'ArrowDown':
                    if (this.dy !== -1) {
                        this.dx = 0;
                        this.dy = 1;
                    }
                    break;
                case 'ArrowLeft':
                    if (this.dx !== 1) {
                        this.dx = -1;
                        this.dy = 0;
                    }
                    break;
                case 'ArrowRight':
                    if (this.dx !== -1) {
                        this.dx = 1;
                        this.dy = 0;
                    }
                    break;
                case 'Space':
                    e.preventDefault();
                    this.togglePause();
                    break;
            }
        });
        
        // Mobile controls
        document.querySelectorAll('.d-pad-btn').forEach(btn => {
            btn.addEventListener('click', (e) => {
                const direction = e.target.getAttribute('data-direction');
                
                if (!this.gameRunning && !this.gamePaused) {
                    this.startGame();
                }
                
                switch(direction) {
                    case 'up':
                        if (this.dy !== 1) {
                            this.dx = 0;
                            this.dy = -1;
                        }
                        break;
                    case 'down':
                        if (this.dy !== -1) {
                            this.dx = 0;
                            this.dy = 1;
                        }
                        break;
                    case 'left':
                        if (this.dx !== 1) {
                            this.dx = -1;
                            this.dy = 0;
                        }
                        break;
                    case 'right':
                        if (this.dx !== -1) {
                            this.dx = 1;
                            this.dy = 0;
                        }
                        break;
                }
            });
        });
        
        // Pause button
        this.pauseBtn.addEventListener('click', () => {
            this.togglePause();
        });
        
        // Restart button
        this.restartBtn.addEventListener('click', () => {
            this.restartGame();
        });
        
        // Touch gestures for mobile
        let touchStartX = 0;
        let touchStartY = 0;
        
        this.canvas.addEventListener('touchstart', (e) => {
            e.preventDefault();
            touchStartX = e.touches[0].clientX;
            touchStartY = e.touches[0].clientY;
            
            if (!this.gameRunning && !this.gamePaused) {
                this.startGame();
            }
        });
        
        this.canvas.addEventListener('touchend', (e) => {
            e.preventDefault();
            const touchEndX = e.changedTouches[0].clientX;
            const touchEndY = e.changedTouches[0].clientY;
            
            const dx = touchEndX - touchStartX;
            const dy = touchEndY - touchStartY;
            
            if (Math.abs(dx) > Math.abs(dy)) {
                // Horizontal swipe
                if (dx > 0 && this.dx !== -1) {
                    this.dx = 1;
                    this.dy = 0;
                } else if (dx < 0 && this.dx !== 1) {
                    this.dx = -1;
                    this.dy = 0;
                }
            } else {
                // Vertical swipe
                if (dy > 0 && this.dy !== -1) {
                    this.dx = 0;
                    this.dy = 1;
                } else if (dy < 0 && this.dy !== 1) {
                    this.dx = 0;
                    this.dy = -1;
                }
            }
        });
    }
    
    startGame() {
        this.gameRunning = true;
        this.gamePaused = false;
        this.gameOverScreen.classList.add('hidden');
    }
    
    togglePause() {
        if (this.gameRunning) {
            this.gamePaused = !this.gamePaused;
            this.pauseBtn.textContent = this.gamePaused ? '▶️' : '⏸️';
        }
    }
    
    generateFood() {
        this.food = {
            x: Math.floor(Math.random() * this.tileCount),
            y: Math.floor(Math.random() * this.tileCount)
        };
        
        // Make sure food doesn't spawn on snake
        for (let segment of this.snake) {
            if (segment.x === this.food.x && segment.y === this.food.y) {
                this.generateFood();
                return;
            }
        }
    }
    
    update() {
        if (!this.gameRunning || this.gamePaused) return;
        
        const head = {x: this.snake[0].x + this.dx, y: this.snake[0].y + this.dy};
        
        // Check wall collision
        if (head.x < 0 || head.x >= this.tileCount || head.y < 0 || head.y >= this.tileCount) {
            this.gameOver();
            return;
        }
        
        // Check self collision
        for (let segment of this.snake) {
            if (head.x === segment.x && head.y === segment.y) {
                this.gameOver();
                return;
            }
        }
        
        this.snake.unshift(head);
        
        // Check food collision
        if (head.x === this.food.x && head.y === this.food.y) {
            this.score += 10;
            this.scoreElement.textContent = this.score;
            this.generateFood();
        } else {
            this.snake.pop();
        }
    }
    
    draw() {
        // Clear canvas
        this.ctx.fillStyle = 'rgba(20, 20, 40, 0.8)';
        this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
        
        // Draw grid
        this.ctx.strokeStyle = 'rgba(255, 255, 255, 0.1)';
        this.ctx.lineWidth = 1;
        for (let i = 0; i <= this.tileCount; i++) {
            this.ctx.beginPath();
            this.ctx.moveTo(i * this.gridSize, 0);
            this.ctx.lineTo(i * this.gridSize, this.canvas.height);
            this.ctx.stroke();
            
            this.ctx.beginPath();
            this.ctx.moveTo(0, i * this.gridSize);
            this.ctx.lineTo(this.canvas.width, i * this.gridSize);
            this.ctx.stroke();
        }
        
        // Draw snake
        this.snake.forEach((segment, index) => {
            if (index === 0) {
                // Head
                this.ctx.fillStyle = '#4ecdc4';
                this.ctx.shadowColor = '#4ecdc4';
                this.ctx.shadowBlur = 10;
            } else {
                // Body
                this.ctx.fillStyle = '#45b7aa';
                this.ctx.shadowBlur = 5;
            }
            
            this.ctx.fillRect(
                segment.x * this.gridSize + 1,
                segment.y * this.gridSize + 1,
                this.gridSize - 2,
                this.gridSize - 2
            );
        });
        
        // Draw food
        this.ctx.fillStyle = '#ff6b6b';
        this.ctx.shadowColor = '#ff6b6b';
        this.ctx.shadowBlur = 15;
        this.ctx.beginPath();
        this.ctx.arc(
            this.food.x * this.gridSize + this.gridSize / 2,
            this.food.y * this.gridSize + this.gridSize / 2,
            this.gridSize / 2 - 2,
            0,
            2 * Math.PI
        );
        this.ctx.fill();
        
        // Reset shadow
        this.ctx.shadowBlur = 0;
        
        // Draw pause overlay
        if (this.gamePaused) {
            this.ctx.fillStyle = 'rgba(0, 0, 0, 0.7)';
            this.ctx.fillRect(0, 0, this.canvas.width, this.canvas.height);
            
            this.ctx.fillStyle = 'white';
            this.ctx.font = '24px Arial';
            this.ctx.textAlign = 'center';
            this.ctx.fillText('PAUSED', this.canvas.width / 2, this.canvas.height / 2);
            this.ctx.fillText('Press SPACE or ⏸️ to resume', this.canvas.width / 2, this.canvas.height / 2 + 30);
        }
        
        // Draw start message
        if (!this.gameRunning && !this.gamePaused) {
            this.ctx.fillStyle = 'rgba(255, 255, 255, 0.9)';
            this.ctx.font = '20px Arial';
            this.ctx.textAlign = 'center';
            this.ctx.fillText('Press any arrow key or tap to start!', this.canvas.width / 2, this.canvas.height / 2);
        }
    }
    
    gameOver() {
        this.gameRunning = false;
        this.gamePaused = false;
        
        // Update high score
        if (this.score > this.highScore) {
            this.highScore = this.score;
            this.highScoreElement.textContent = this.highScore;
            localStorage.setItem('snakeHighScore', this.highScore);
        }
        
        // Show game over screen
        this.finalScoreElement.textContent = this.score;
        this.gameOverScreen.classList.remove('hidden');
        
        this.pauseBtn.textContent = '⏸️';
    }
    
    restartGame() {
        this.snake = [{x: 10, y: 10}];
        this.dx = 0;
        this.dy = 0;
        this.score = 0;
        this.scoreElement.textContent = this.score;
        this.generateFood();
        this.gameOverScreen.classList.add('hidden');
        this.gameRunning = false;
        this.gamePaused = false;
        this.pauseBtn.textContent = '⏸️';
    }
    
    gameLoop() {
        this.update();
        this.draw();
        
        setTimeout(() => {
            this.gameLoop();
        }, 150); // Game speed
    }
}

// Initialize game when page loads
document.addEventListener('DOMContentLoaded', () => {
    new SnakeGame();
});