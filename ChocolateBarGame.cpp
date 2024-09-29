/**
 * @file ChocolateBarGame.cpp
 * @brief Plays a session of chocolate game
 * @date September 28th, 2024
 * @author Sarah Akhtar
 */

#include "ChocolateBarGame.h"
#include <iostream>
#include <random>
#include <ctime>

#pragma mark - Console Color Variables

/// Creates colors for chocolate, instructions, and losses
const string ChocolateBarGame::LIGHT_BROWN = "\033[38;5;130m";
const string ChocolateBarGame::BROWN = "\033[38;5;130m";
const string ChocolateBarGame::RED = "\033[31m";
const string ChocolateBarGame::YELLOW = "\033[33m";
const string ChocolateBarGame::GREEN = "\033[32m";
const string ChocolateBarGame::BLUE = "\033[34m";
const string ChocolateBarGame::RESET = "\033[0m";

#pragma mark - Chocolate Bar Game Constructor

/**
 * @brief Constructs a new ChocolateBarGame
 * @param m The number of rows in the chocolate bar (positive integer)
 * @param n The number of columns in the chocolate bar (positive integer)
 * @param sr The valid row index of the spoiled piece (converted to 0-index)
 * @param sc The valid column index of the spoiled piece (converted to 0-index)
 */
ChocolateBarGame::ChocolateBarGame(const int m, const int n, const int sr, const int sc) {
	// Sets chocolate bar dimensions and creates visualization of 'O's
	chocolateRows = m, chocolateCols = n;
	chocolateBar = vector<vector<char>> (chocolateRows, vector<char> (chocolateCols, 'O'));

	// Sets spoiled piece dimensions and creates visualization of 'X'
	spoiledRow = sr - 1, spoiledCol = sc - 1;
	chocolateBar.at(spoiledRow).at(spoiledCol) = 'X';

	// Determines which player will go first based on the following algorithm:
	//  - If m is even and n is even OR if n is odd and m is odd, player first
	//  - If m is even and n is odd OR if n is odd and m is even, computer first
	isPlayerTurn = ((m % 2 == 1 && n % 2 == 1) || (m % 2 == 0 && n % 2 == 0));
	isGameOver = false;
}

#pragma mark - Chocolate Bar Visualization

/**
 * @brief Prints out current chocolate bar
 * - The spoiled piece will be a light shade of brown
 * - Regular pieces will be a darker shade of brown
 */
void ChocolateBarGame::printChocolateBar() const {
	// Avoids printing if game is over
	if (isGameOver) { return; }

	// Prints current layout of chocolate bar with spoiled piece
	cout << GREEN << "Chocolate Bar:" << RESET << endl;
	for (int row = 0; row < chocolateRows; ++row) {
		for (int col = 0; col < chocolateCols; ++col) {
			if (chocolateBar.at(row).at(col) == 'O') { cout << BROWN; }
			else { cout << YELLOW; }
			cout << chocolateBar.at(row).at(col) << ' ';
		}
		cout << endl;
	}
	cout << RESET << endl;
}

#pragma mark - Direction Selection/Update

/**
 * @brief Updates board from valid user direction selection
 * - Determines the row or column to be eaten by direction
 * - Appends the appropriate row/column to an array to display
 * - Checks if a spoiled piece was consumed to end game
 * - Prints chocolate consumed for player if not end game
 * @param direction Representing the direction (u/d/l/r)
 */
void ChocolateBarGame::updateChocolateBarDirection(const char direction) {
	// Create data to store eaten row/column
	vector<vector<char>> eaten;
	bool eatsSpoiled = false;

	// Gets upper row from chocolate to display after removal
	if (direction == 'u') {
		eaten = vector<vector<char>>(1, vector<char>(chocolateCols));
		for (int j = 0; j < chocolateCols; ++j) eaten[0][j] = chocolateBar[0][j];
		eatsSpoiled = (spoiledRow == 0);
		if (!eatsSpoiled) {
			chocolateBar.erase(chocolateBar.begin());
			chocolateRows--;
			spoiledRow--;
		}
	// Gets lower row from chocolate to display after removal
	} else if (direction == 'd') {
		eaten = vector<vector<char>>(1, vector<char>(chocolateCols));
		for (int j = 0; j < chocolateCols; ++j) eaten[0][j] = chocolateBar[chocolateRows - 1][j];
		eatsSpoiled = (spoiledRow == chocolateRows - 1);
		if (!eatsSpoiled) {
			chocolateBar.pop_back();
			chocolateRows--;
		}
	// Gets left column from chocolate to display after removal
	} else if (direction == 'l') {
		eaten = vector<vector<char>>(chocolateRows, vector<char>(1));
		for (int i = 0; i < chocolateRows; ++i) eaten[i][0] = chocolateBar[i][0];
		eatsSpoiled = (spoiledCol == 0);
		if (!eatsSpoiled) {
			for (int i = 0; i < chocolateRows; ++i) {
				chocolateBar[i].erase(chocolateBar[i].begin());
			}
			chocolateCols--;
			spoiledCol--;
		}
	// Gets right column from chocolate to display after removal
	} else if (direction == 'r') {
		eaten = vector<vector<char>>(chocolateRows, vector<char>(1));
		for (int i = 0; i < chocolateRows; ++i) eaten[i][0] = chocolateBar[i][chocolateCols - 1];
		eatsSpoiled = (spoiledCol == chocolateCols - 1);
		if (!eatsSpoiled) {
			for (int i = 0; i < chocolateRows; ++i) {
				chocolateBar[i].pop_back();
			}
			chocolateCols--;
		}
	}

	// Checks if the spoiled piece is consumed and sets game over
	if (eatsSpoiled) {
		isGameOver = true;
		if (isPlayerTurn) { cout << RED << "You ate the spoiled piece. You lose!" << endl; }
		else { cout << GREEN << "Computer ate the spoiled piece. You win!" << endl; }
		return;
	}

	// Displays appropriate message for which player consumed chocolate
	if (isPlayerTurn) { cout << GREEN << "Player eats:" << RESET << endl; }
	else { cout << GREEN << "Computer eats:" << RESET << endl; }
	for (const auto & row: eaten) {
		cout << LIGHT_BROWN;
		for (const char c: row) cout << c << ' ';
		cout << endl;
	}
	cout << RESET << endl;
}

#pragma mark - Computer Move Selection

/**
 * @brief Calculates valid computer move from current chocolate
 * @return A random direction among the valid moves available
 */
char ChocolateBarGame::initiateComputerMove() const {
	// Determines valid computer move from current chocolate
	vector<char> validDirections;
	if (isValidDirection('u') && spoiledRow != 0) validDirections.push_back('u');
	if (isValidDirection('d') && spoiledRow != chocolateRows - 1) validDirections.push_back('d');
	if (isValidDirection('l') && spoiledCol != 0) validDirections.push_back('l');
	if (isValidDirection('r') && spoiledCol != chocolateCols - 1) validDirections.push_back('r');
	if (validDirections.empty()) return 'x';

	// Returns a random direction among valid directions
	static mt19937 rng(time(nullptr));
	uniform_int_distribution <int> dist(0, validDirections.size() - 1);
	return validDirections[dist(rng)];
}

#pragma mark - Direction Selection Validation

/**
 * @brief Determines if a direction selected by computer is valid
 * @return Whether the computer-selected direction is valid for the chocolate board
 */
bool ChocolateBarGame::isValidDirection(const char direction) const {
	// Determines if a move is valid for the computer to make
	if (direction == 'u' && spoiledRow >= 0) return true;
	if (direction == 'd' && spoiledRow <= chocolateRows - 1) return true;
	if (direction == 'l' && spoiledCol >= 0) return true;
	if (direction == 'r' && spoiledCol <= chocolateCols - 1) return true;
	return false;
}

#pragma mark - Game Initialization Method

/**
 * @brief Creates a game loop until the game ends and updates the game
 * - Loops from game beginning to end, playing all operations
 * - Operates between player and computer turns each iteration
 * - Prints chocolate bar each time after update
 */
void ChocolateBarGame::startGame() {
	// Initially prints the board after configuration
	printChocolateBar();

	// Loops from start of game to end, playing the game
	while (!isGameOver) {
		char userDirection;

		// Gets valid user input for the player's turn
		if (isPlayerTurn) {
			cout << BLUE << "Enter your move (u/d/l/r): " << RESET;
			cin >> userDirection;
			if (!isValidDirection(userDirection)) {
				cout << RED << "Invalid move. Try again." << RESET << endl;
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				continue;
			}
		// Gets valid computer move and performs update
		} else {
			userDirection = initiateComputerMove();
			if (userDirection == 'x') {
				cout << GREEN << "Computer has no valid moves. You win!" << RESET << endl;
				return;
			}
			cout << BLUE << "Computer's move: " << userDirection << RESET << endl;
		}

		// Updates the chocolate bar from user selection and prints update
		updateChocolateBarDirection(userDirection);
		printChocolateBar();

		// Switches player turn each run
		isPlayerTurn = !isPlayerTurn;
	}
}