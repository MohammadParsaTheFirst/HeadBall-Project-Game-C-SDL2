content = """
# Two-Dimensional Football Game

This project is a two-dimensional football game developed using C++ and SDL2. The game features two players and includes various functionalities such as settings, player statistics, league tables, and more.

## Table of Contents
- Features
- Installation
- Usage
- Game Mechanics
- Controls
- Special Powers
- Credits

## Features
- **Main Menu**: Includes options for settings, entering player names, viewing league tables, and starting the game.
- **Player Statistics**: Displays player information such as scores, number of games, wins, losses, etc.
- **League Table**: Shows player names, number of games, wins/draws/losses, goals scored/conceded, goal difference, and points.
- **Game Start**: Allows customization of player characters, ball type, playing field, and game-ending conditions.
- **Animations and Sound Effects**: Includes animations for player entry, fan reactions, and various sound effects for different game events.
- **Pause and Resume**: Ability to pause and resume the game.
- **Cheat Codes**: Includes cheat codes for creative gameplay enhancements.
- **Special Powers**: Each player has unique special powers that can be activated during the game.

## Installation
1. Clone the repository:
   \`\`\`bash
   git clone https://github.com/yourusername/football-game.git
   \`\`\`
2. Install the required dependencies and libraries for SDL2.
3. Compile the project using your preferred C++ compiler.

## Usage
1. Run the executable to start the game.
2. Use the main menu to navigate through settings, enter player names, view league tables, and start the game.
3. Customize the game settings before starting a match.
4. Control the players using the keyboard or mouse as per your preference.

## Game Mechanics
- **Player Control**: Players can be controlled using keyboard or mouse. Player 1 uses the arrow keys, and Player 2 uses the \`W\`, \`A\`, \`D\` keys.
- **Ball Interaction**: The ball is thrown from the center of the field at the start and after each goal. The ball's interaction with players is elastic, with a mass ratio of 1:10.
- **Shooting**: The ball can be shot at fixed angles depending on where it hits the player's foot.
- **Game End Conditions**: The game ends when a player reaches a specified number of goals. If both players have the same number of goals below the final goal count, the game is declared a draw.

## Controls
- **Player 1**: Arrow keys for movement.
- **Player 2**: \`W\`, \`A\`, \`D\` keys for movement.
- **Cheat Powers**: There are some cheat codes that covers your Goal with a red wall, so you won't receive any goals by your opponnent.

## Special Powers
1. **Triple Clone**: Creates three clones of the player for 8 seconds, all moving simultaneously.
2. **Head Fire Ball**: Allows the player to jump and shoot the ball with their head, causing the opponent to be stunned for 3 seconds if hit.
3. **Kick Fire Ball**: Allows the player to shoot the ball powerfully with their foot, causing the opponent to be stunned for 3 seconds if hit.
4. **Punch (Mortal Kombat)**: Stuns the opponent for 3 seconds upon hitting them.
5. **Thief**: Randomly executes one of the above powers.
6. **Power Bar**: Each player has a power bar that fills up linearly over time. Scoring a goal accelerates the filling process. The power bar is displayed on the scoreboard.
7. **Obstacles**: Includes walls of various shapes and sizes, and doors that open and close, affecting the ball's movement.
8. **Pause Menu**: Allows returning to the main menu, exiting the game, and accessing settings.
9. **Scoreboard**: Displays player names and goal counts.
10. **Power-Ups**: Collectible items on the field that speed up the power bar filling when hit by the ball or player.
11. **Background Music**: Adds an immersive audio experience to the game.

## Credits
- Developed by Your Name
- Special thanks to the SDL2 community for their support and resources.
"""
