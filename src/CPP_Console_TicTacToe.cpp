//============================================================================
// Name        : CPP_Console_TicTacToe.cpp
// Author      : Kyler McMullin (wades39)
// Version     : 2022/01/09
// Copyright   : Your copyright notice
// Description : C++ implementation of TicTacToe that can be played in the Windows Command Prompt
//============================================================================

#include <iostream> // default import
#include <string> // imported to use strings
#include <limits> // imported to use limit in clearing cin buffer

using namespace std;

int numSpaces;

int checkWin(int **spcs) {
	bool isMatch = true;

	// Check each row
	for (int i = 0; i < numSpaces; i++) {
		if (spcs[i][0] == 0) {
			continue;
		}
		isMatch = true;

		for (int j = 1; j < numSpaces; j++) {
			isMatch = isMatch && spcs[i][j - 1] == spcs[i][j];
		}
		if (isMatch) {
			return (spcs[i][0]);
		}
	}

	// Check each column
	for (int i = 0; i < numSpaces; i++) {
		if (spcs[0][i] == 0) {
			continue;
		}
		isMatch = true;

		for (int j = 1; j < numSpaces; j++) {
			isMatch = isMatch && spcs[j - 1][i] == spcs[j][i];
		}
		if (isMatch) {
			return (spcs[0][i]);
		}
	}

	// Check TLBR diagonal
	isMatch = true;
	for (int i = 0; i < numSpaces - 1; i++) {
		if (spcs[i][i] == 0) {
			isMatch = false;
			break;
		}
		isMatch = isMatch && spcs[i][i] == spcs[i + 1][i + 1];
	}

	if (isMatch) {
		return (spcs[0][0]);
	}

	// Check BLTR diagonal
	isMatch = true;
	for (int i = numSpaces - 1; i > 0; i--) {

		int j = numSpaces - (i + 1);

		if (spcs[i][j] == 0) {
			isMatch = false;
			break;
		}

		isMatch = isMatch && spcs[i][j] == spcs[i - 1][j + 1];
	}
	if (isMatch) {
		return (spcs[0][numSpaces - 1]);
	}

	// If we get here, the game is a tie.
	return (0);
}

string parseGameSpace(int **spaces) {

	string grid = "";

	string emptyRowSegment = "   #";
	string emptyRowSegmentEnd = "   \n";
	string columnDivider = "####";
	string columnDividerEnd = "###\n";
	string player1Symbol = " X ";
	string player2Symbol = " O ";

	for (int i = 0; i < numSpaces; i++) {
		string line = "";
		for (int k = 0; k < numSpaces - 1; k++) {
			line += emptyRowSegment;
		}
		line += emptyRowSegmentEnd;

		for (int j = 0; j < numSpaces; j++) {
			switch (spaces[i][j]) {
				case 1:
					line += player1Symbol;
					break;
				case 2:
					line += player2Symbol;
					break;
				default:
					line += "   ";
					break;
			}

			if (j == numSpaces - 1)
				line += "\n";
			else
				line += "#";

		}

		for (int k = 0; k < numSpaces - 1; k++) {
			line += emptyRowSegment;
		}
		line += emptyRowSegmentEnd;

		if (i < numSpaces - 1) {
			for (int k = 0; k < numSpaces - 1; k++) {
				line += columnDivider;
			}
			line += columnDividerEnd;
		}

		grid += line;
	}

	return (grid);

}

// convert a string to lowercase and return it
string toLowerCase(string str) {

	string lowercase = "";
	locale loc;

	for (auto elem : str)
		lowercase = lowercase + tolower(elem, loc);

	return (lowercase);
}

void flushCin() {

	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

bool checkValidMove(int **spaces, int move) {

	move -= 1;

	// Calculate the row and column of the move
	int row = move / numSpaces;
	int col = move % numSpaces;

	// Determine whether the move is valid.
	if (spaces[row][col] == 0) {
		return (true);
	}
	return (false);
}

void makeMove(bool player1Turn, int **spaces, int move) {

	move -= 1;

	// Calculate the row and column of the move
	int row = move / numSpaces;
	int col = move % numSpaces;

	// Make the move on the board.
	spaces[row][col] = player1Turn ? 1 : 2;
}

int main() {

	// Get the number of spaces for the game and flush the CIN buffer
	cout
			<< "Welcome to TicTacToe!\nHow many rows/columns would you like the grid to be?"
			<< endl;
	cin >> numSpaces;
	flushCin();

	cout << "Generating a grid with " << numSpaces << " rows and columns..."
			<< endl;

	// Declare variables necessary for the game to operate.
	int player1Score;
	int player2Score;
	int numMoves;
	int playerMove;

	bool player1Turn;
	bool player1Starts;
	bool keepPlaying;

	player1Score = 0;
	player2Score = 0;
	numMoves = 0;
	playerMove = 0;

	// Build a 2D array of integers to show the ownership of each space in the grid.
	// 0 is neutral, 1 is player 1, 2 is player 2
	int **spaces;
	spaces = new int*[numSpaces];

	for (int i = 0; i < numSpaces; i++) {
		spaces[i] = new int[numSpaces];
	}

	for (int i = 0; i < numSpaces; i++) {
		for (int j = 0; j < numSpaces; j++) {
			spaces[i][j] = 0;
		}
	}

	cout << "Done generating..." << endl;

	// Initialize the variables needed to determine the game state for the first game.
	player1Turn = true;
	player1Starts = true;

	// Loop the game as long as the players say they want to continue playing
	do {

		// Reset the keepPlaying value so that the game doesn't go into an infinite loop.
		keepPlaying = false;

		// Initialize the variables needed for running this game.
		numMoves = 0;

		if (player1Starts) {
			player1Turn = true;
		} else {
			player1Turn = false;
		}

		// Core game loop
		while (numMoves <= ((numSpaces * numSpaces) - 1)) {

			// Print out the grid
			cout << "The current game grid is:\n" << endl;
			cout << parseGameSpace(spaces) << endl;
			cout << "Player " << (player1Turn ? 1 : 2) << "\'s turn!" << endl;

			bool validMove = false;

			// Loop the player input until a valid move is detected.
			do {
				cout << "Enter a number (1 thru " << (numSpaces * numSpaces)
						<< ") to choose a space:  ";
				// Get player input
				cin >> playerMove;

				flushCin();

				validMove = checkValidMove(spaces, playerMove);

				if (!validMove) {
					cout << "Invalid move! Please try again." << endl;
				}

			} while (!validMove);


			cout << endl << endl << endl << endl;

			makeMove(player1Turn, spaces, playerMove);

			numMoves++;

			if (numMoves >= numSpaces) {
				if (checkWin(spaces) != 0)
					break;
			}

			player1Turn = !player1Turn;
		}

		cout << endl << endl << endl;
		// Output the appropriate message for the game's ending.
		switch (checkWin(spaces)) {
			case 1:
				cout << "PLAYER 1 WINS!!!" << endl;
				player1Score++;
				break;
			case 2:
				cout << "PLAYER 2 WINS!!!" << endl;
				player2Score++;
				break;
			default:
				cout << "GAME TIE!!!" << endl;
				break;
		}
		cout << parseGameSpace(spaces) << endl << endl << endl;
		cout << "Player 1 Score:  " << player1Score << endl;
		cout << "Player 2 Score:  " << player2Score << endl;

		// Invert player1Starts so that player 2 will start the next game (if the players continue).
		player1Starts = !player1Starts;

		// Ask the players whether or not they would like to keep playing. If so, reset the loop.
		// Else, end the loop and print out a farewell message.
		cout << "Would you like to keep playing? (Y/N):  ";
		string resp;
		getline(cin, resp);

		keepPlaying = (toLowerCase(resp) == "y");

		// Reset the grid
		for (int i = 0; i < numSpaces; i++) {
			for (int j = 0; j < numSpaces; j++) {
				spaces[i][j] = 0;
			}
		}

		// delete the response so that we don't leak any memory.
		delete &resp;

	} while (keepPlaying);

	// Print out a farewell message.
	cout << "Thank you for playing my game!" << endl;

	for (int i = 0; i < numSpaces; i++) {
		delete &spaces[i];
	}
	delete &spaces;

	return (0);
}
