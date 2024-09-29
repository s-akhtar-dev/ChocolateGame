# Game Theory Puzzle: A Chocolate Variation of Nim

This repository contains a console-based implementation of the mathematical game Nim, where two players alternate turns to remove objects from a predefined group. In this variation, the game is played using a chocolate bar divided into an m × n grid, with the dimensions specified by the user. A "spoiled" piece, also chosen by the user, is the square that players seek to avoid. On each turn, players select a direction (up, down, left, or right) and remove the corresponding row or column from the chocolate bar. The game concludes when one player is forced to take the spoiled piece, resulting in their loss.

## Table of Contents

- [Winning Algorithm](#winning-algorithm)
- [Nim Variation Chocolate Game Rules](#nim-variation-chocolate-game-rules)
- [Game Installation](#game-installation)
- [How to Play Nim Game](#how-to-play-nim-game)
- [Game License](#game-license)

## Winning Algorithm

The game employs a deterministic approach that ensures the computer will always win, regardless of the player's strategy. This method is mathematically based on the selection of the starting player, which is determined by the dimensions of the chocolate bar (m × n) according to the following rules:
- If both m and n are even, or both m and n are odd, the player goes first.
- If one dimension is even and the other is odd, the computer goes first.
This selection mechanism places the computer in a guaranteed winning position as the alternating moves will ultimately lead to the user's defeat. The mathematical reasoning behind the first-player selection is based on the parity (evenness or oddness) of the chocolate bar grid, which is explained as follows:

**Symmetry in Even-Even and Odd-Odd Dimensions**
- When both dimensions (m and n) are either even or odd, the chocolate has a symmetrical pattern that the computer can use to create a winning position. In this case, the player is forced to deal with the spoiled piece as the number of potential moves allows the computer to control the game flow. After the computer’s initial move, the number of cuts required to reduce the chocolate bar to a single piece is even. As a result, the last player to make a move will always be the user, making a victory impossible. Therefore, the algorithm is designed to ensure that the player always goes first.
  
**Asymmetry in Even-Odd or Odd-Even Dimensions**
- On the other hand, when one dimension is even and the other is odd, the grid has an inherent asymmetry. In this case, after the computer takes its move, the remaining moves needed to reach the spoiled piece will be odd. As a result, the player who starts the game (the user, in this case) will inevitably find themselves in a winning position. To ensure that the computer will always win, the computer will go first in such situations.

This algorithm guarantees a winning outcome for the computer 100% of the time, regardless of grid size or the location of the spoiled piece. To create a better gaming experience and a replication of randomness, the computer selects various valid breaks in the chocolate bar, giving the illusion that the player has a chance to win. However, as shown by this strategic algorithm, the user will ultimately always lose.

## Nim Variation Chocolate Game Rules

1. The game starts with a rectangular chocolate bar made up of smaller (m x n) squares.
2. Players (computer and user) take turns choosing a direction and breaking the chocolate bar at that point.
4. The player who is forced to eat the last square remaining loses the game.

## Game Installation

To run the Chocolate Game on your local machine, follow these steps:

1. Clone the ChocolateGame repository:
   ``` bash
   git clone https://github.com/s-akhtar-dev/ChocolateGame.git
   ```
2. Navigate to the ChocolateGame project directory:
   ```
   cd ChocolateGame
   ```
3. Compile the game as chocolate_game:
   ```
   g++ -std=c++11 main.cpp ChocolateBarGame.cpp -o chocolate_game
   ```
4. Run the game:
   ```
   ./chocolate_game
   ```


## How to Play Nim Game

1. When prompted, enter the dimensions of the chocolate bar (rows and columns).
2. Specify the spoiled piece within a valid area within the chocolate bar dimensions.
3. You and the computer will take turns entering the direction of the row/column to be eaten.
4. The game continues until one player is forced to eat the spoiled square.


## Game License

This project is open source and available under the [MIT License](LICENSE).
Enjoy playing the Chocolate Game!
