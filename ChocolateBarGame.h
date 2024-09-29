/**
 * @file main.cpp
 * @brief COMP 157 Chocolate Game
 * @date September 28th, 2024
 * @author Sarah Akhtar
 */

#ifndef CHOCOLATEBARGAME_H
#define CHOCOLATEBARGAME_H

#include <vector>
using namespace std;

/**
 * @class ChocolateBarGame
 * @brief Represents a chocolate bar game simulation
 *
 * @description
 * The ChocolateBarGame is a player-versus-computer game in which each player
 * takes turns breaking rows or columns from a user-specified chocolate bar.
 * The bar has dimensions of m x n and has one spoiled pieced. The objective
 * of the game is to avoid consuming the spoiled piece.
 *
 * Game Rules:
 * - The chocolate bar is represented as a 2-D vector of m rows and n columns.
 * - One piece at location (sr, sc) is marked as spoiled from the user's input.
 * - Players (user and computer) take turns choosing a direction to break row/column.
 * - The selected row or column is broken off, displayed, and eaten by the player.
 * - The player who is forced to eat the spoiled piece loses.
 *
 * @note
 * - When coordinates are specified, they are 1-indexed in the console
 * - When the coordinates are initialized in the class, they are 0-indexed
 *
 */
class ChocolateBarGame {
    private:
        /// Dimensions, chocolate bar, and control
        int chocolateRows;
        int chocolateCols;
        int spoiledRow;
        int spoiledCol;
        vector<vector<char>> chocolateBar;
        bool isGameOver;
        bool isPlayerTurn;

        /// Methods for displaying, updates, and moves
        void printChocolateBar() const;
        bool isValidDirection(char direction) const;
        void updateChocolateBarDirection(char direction);
        char initiateComputerMove() const;

    public:
        /// Colors for console output display
        static const string LIGHT_BROWN;
        static const string BROWN;
        static const string RED;
        static const string YELLOW;
        static const string GREEN;
        static const string BLUE;
        static const string RESET;

        /// Constructor and game initialization
        ChocolateBarGame(int m, int n, int sr, int sc);
        void startGame();
};

#endif //CHOCOLATEBARGAME_H
