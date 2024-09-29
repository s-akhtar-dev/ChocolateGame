/**
 * @file main.cpp
 * @brief COMP 157 Chocolate Game
 * @date September 28th, 2024
 * @author Sarah Akhtar
 */

#include "ChocolateBarGame.h"
#include <iostream>
using namespace std;

#pragma mark - Game Initialization Declarations

/// Creates instructions and game
void printStartMessage();
void createNewChocolateGame();

#pragma mark - Game Initialization

int main() {
    createNewChocolateGame();
    return 0;
}

#pragma mark - Game Initialization Definitions

/**
 * @brief Generates default game instructions and welcome
 * - Game is 1-indexed from default (0 indices are rejected)
 */
void printStartMessage() {
    cout << ChocolateBarGame::GREEN << endl;
    cout << "x--------------------------------x" << endl;
    cout << "| Welcome to the Chocolate Game! |" << endl;
    cout << "|  - This game is 1-indexed, so  |" << endl;
    cout << "|    entering 0,0 as the spoiled |" << endl;
    cout << "|    piece would be invalid!     |" << endl;
    cout << "|  - Thank you and enjoy!        |" << endl;
    cout << "x--------------------------------x" << endl;
    cout << ChocolateBarGame::RESET << endl;
}

/**
 * @brief Creates a chocolate game from dimensions
 * - Takes in valid chocolate dimensions (m, n)
 * - Takes in valid spoiled dimensions (sr, sc)
 * - Creates a new game from ChocolateBarGame to play
 */
void createNewChocolateGame() {
    // Prints out initial instructions
    printStartMessage();

    // Requests input for user dimensions of chocolate (m, n)
    int chocolateRows, chocolateCols, spoiledRow, spoiledCol;
    cout << ChocolateBarGame::BLUE << "Enter dimensions of chocolate bar (m n): ";
    cout << ChocolateBarGame::RESET;
    cin >> chocolateRows >> chocolateCols;

    // Checks for valid input and if not, requests again
    while (cin.fail() || chocolateRows < 1 || chocolateCols < 1) {
        cout << ChocolateBarGame::RED << "--Please Invalid dimensions!--" << endl;
        cout << ChocolateBarGame::BLUE << "Enter dimensions of chocolate bar (m n): ";
        cout << ChocolateBarGame::RESET;
        cin >> chocolateRows >> chocolateCols;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Requests input for user dimensions of spoiled piece (sr, sc)
    cout << ChocolateBarGame::BLUE << "Enter spoiled piece location (row col): ";
    cin >> spoiledRow >> spoiledCol;

    // Checks for valid input and if not, requests again
    while ((spoiledRow < 1 || spoiledCol < 1) ||
           (spoiledRow > chocolateRows || spoiledCol > chocolateCols)) {
        cout << ChocolateBarGame::RED << "--Please Invalid dimensions!--" << endl;
        cout << ChocolateBarGame::BLUE << "Enter spoiled piece location (row col): ";
        cout << ChocolateBarGame::RESET;
        cin >> spoiledRow >> spoiledCol;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Creates a new ChocolateBarGame and starts new session
    ChocolateBarGame chocolateGame(chocolateRows, chocolateCols, spoiledRow, spoiledCol);
    chocolateGame.startGame();
}