# CONTROLS.md

# Snake Game Controls

## Gameplay Controls

### Movement
- **Arrow Keys**: Primary movement controls
  - ↑ **Up Arrow**: Move snake up
  - ↓ **Down Arrow**: Move snake down  
  - ← **Left Arrow**: Move snake left
  - → **Right Arrow**: Move snake right

- **WASD Keys**: Alternative movement controls
  - **W**: Move snake up
  - **S**: Move snake down
  - **A**: Move snake left
  - **D**: Move snake right

### Game Controls
- **R**: Restart game (only available when game over)
- **Escape**: Close the game window

## Gameplay Rules

### Basic Movement
- Snake moves continuously in its current direction
- Change direction by pressing movement keys
- Snake cannot reverse directly into its own body
- Movement changes take effect on the next game tick

### Winning Condition
- Eat food to grow longer and increase score
- Each food item gives 10 points
- Game speed increases as you score more points

### Losing Conditions
- Snake hits the window boundaries (walls)
- Snake collides with its own body

### Difficulty Progression
- Game starts at a comfortable speed
- Speed increases every 50 points (5 food items)
- Speed increase makes the game progressively more challenging

## Tips for Success

### Movement Strategy
1. **Plan Ahead**: Think about your snake's path before making turns
2. **Use the Edges**: Utilize the wall boundaries to your advantage for tight maneuvers
3. **Avoid Trapping Yourself**: Don't box yourself into corners
4. **Spiral Technique**: Create spirals to buy time in tight spaces

### Scoring Tips
1. **Consistent Movement**: Develop a rhythm for smooth gameplay
2. **Risk vs Reward**: Sometimes it's safer to take a longer path to food
3. **Body Management**: Keep track of your snake's length to avoid self-collision
4. **Speed Adaptation**: Adjust your play style as the game gets faster

### Advanced Techniques
1. **Wall Riding**: Use walls to guide your movement in straight lines
2. **Corner Cutting**: Make tight turns by utilizing precise timing
3. **Space Creation**: Deliberately create open spaces for future maneuvering
4. **Patience**: Don't rush toward food if it puts you in danger

## Accessibility Features

### Input Options
- Multiple control schemes (arrows + WASD) accommodate different preferences
- Clear visual feedback for all game states
- Simple, intuitive control mapping

### Visual Clarity
- High contrast colors between snake, food, and background
- Clear distinction between snake head and body
- Simple grid-based layout for easy tracking

## Customization Notes

If you want to modify controls, edit the `handleInput()` function in `Game.cpp`: