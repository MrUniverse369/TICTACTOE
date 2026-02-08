# Tic Tac Toe (C++ Console Game)

## Overview

This project is a console-based Tic Tac Toe game developed in C++, designed for two players competing locally. The game follows traditional Tic Tac Toe rules and includes a coin toss system to randomly determine which player goes first. The implementation focuses on structured game flow, robust input validation, and clear win, loss, and draw detection, providing a smooth and interactive command-line experience.

## Features

- Console-based **two-player Tic Tac Toe** game built in **C++**
- Random **coin toss** at the start of each game to decide the first player
- Turn-based gameplay with automatic turn switching
- Board positions labeled **A–I** for intuitive input
- Strong input validation to ensure:
  - Alphabetical input only
  - Valid board positions (A–I)
  - Prevention of overwriting occupied spaces
- Dynamic board rendering after every move
- Full win-state detection:
  - Horizontal, vertical, and diagonal combinations
- Draw detection when all board spaces are filled
- Menu system allowing players to start or quit the game

## Controls

### Menu
- Enter **1** to start a new game
- Enter **2** to quit the application

### Gameplay Input
- Players take turns entering a letter between **A–I** to place their mark
- **Player One:** `X`
- **Player Two:** `O`

### Game Rules
- Players alternate turns placing their symbol on the board
- A player wins by placing **three matching symbols in a row**
  - Horizontally, vertically, or diagonally
- Invalid or occupied inputs will prompt the player to retry

### Game End Conditions
- **Win:** One player completes a valid three-in-a-row combination
- **Draw:** All board spaces are filled without a winner

