#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include "connect4.h"

using namespace std;





int connect4Board::getTurn() {
	return this->turn;
}

void connect4Board::setTurn(int team) {
	this->turn = team;
}

void connect4Board::changeTurn() {
	this->turn = (this->turn == player) ? computer : player;
}


int changeTurn(const int &currentTurn) {
	return (currentTurn == 1) ? 2 : 1;
}

bool connect4Board::isFull(int column) {
	if (this->at(column, 6) != empty) {
		return true;
	} else {
		return false;
	}
}

bool connect4Board::isValidIndex(int x, int y) {
	if ((x > 6) || (y > 6) || (x < 0) || (y < 0)) {
		return false;
	} else {
		return true;
	}
}

int connect4Board::at(int x, int y) {
	if (!this->isValidIndex(x, y)) {
		cout << x << "," << y << " is an invalid index" << endl;
		exit(0);
	}
	return board[x][y];
}

void connect4Board::setAt(int x, int y, int team) {
	if (!this->isValidIndex(x, y)) {
		cout << x << "," << y << " is an invalid index" << endl;
		exit(0);
	} else if ((team > 2) || (team < 0)) {
		cout << team << " is not a valid team" << endl;
		exit(0);
	}

	board[x][y] = team;

}

int connect4Board::checkWin() {
	// checking to find a horizontal row
	int streak = 0;
	for (int k = 0; k < 7; k++) {

		if (this->at(k, lastY) == turn) {
			streak++;
			//cout << "streak: " << streak << endl;
		}
		else {
			streak = 0;
		}

		if (streak >= 4)
			return turn;
	}

	// checkign for vertical win
	streak = 0;
	for (int k = 0; k < 7; k++) {

		if (this->at(lastX, k) == turn) {
			streak++;
			//cout << "streak: " << streak << endl;
		}
		else {
			streak = 0;
		}

		if (streak >= 4)
			return turn;
	}

	// checking diagonal win

	// finding edge of board
	int r = lastY; int c = lastX;
	while ((r < 6) && (c < 6)) {
		r++;
		c++;
	}

	// going from edge diagonally, checkign for streaks
	streak = 0;
	while ((r >= 0) && (c >= 0)) {
		if (this->at(c, r) == turn) {
			streak++;
		}
		else {
			streak = 0;
		}

		if (streak >= 4) {
			return turn;
		}

		r--;
		c--;

	}

	// finding the edge
	r = lastY; c = lastX;
	while ((r > 0) && (c < 6)) {
		r--;
		c++;
	}

	// looking for streaks
	streak = 0;
	while ((r <= 6) && (c >= 0)) {
		if (this->at(c, r) == turn) {
			streak++;
		}
		else {
			streak = 0;
		}

		if (streak >= 4) {
			return turn;
		}

		r++;
		c--;

	}


	return 0;
}

void connect4Board::dropPiece(int dropLocation) {
	
	
	for (int k = 6; k >= 0; k--) {
		if (this->at(dropLocation, k) != empty) {
			this->setAt(dropLocation, k+1, turn);
			return;
		}
	}
	
	this->setAt(dropLocation, 0, turn);
	return;

}

void connect4Board::displayBoard() {
	cout << endl << endl << endl;

	// provide column numbers
	for (int k = 0; k < 7; k++) {
		cout << k << " ";
	}
	cout << endl << endl;

	// display board fromm top down
	for (int row = 6; row >= 0; row--) {
		for (int col = 0; col < 7; col++) {
			cout << this->at(col, row) << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// checks area around new piece to see if he won
int checkWin(const vector<vector<int> > &board, const int &row, const int &col, const int &turn) {

	// checking to find a horizontal row
	int streak = 0;
	for (int k = 0; k < 7; k++) {

		if (board.at(k).at(row) == turn) {
			streak++;
			//cout << "streak: " << streak << endl;
		}
		else {
			streak = 0;
		}

		if (streak >= 4)
			return turn;
	}

	// checkign for vertical win
	streak = 0;
	for (int k = 0; k < 7; k++) {

		if (board.at(col).at(k) == turn) {
			streak++;
			//cout << "streak: " << streak << endl;
		}
		else {
			streak = 0;
		}

		if (streak >= 4)
			return turn;
	}

	// checking diagonal win

	// finding edge of board
	int r = row; int c = col;
	while ((r < 6) && (c < 6)) {
		r++;
		c++;
	}

	// going from edge diagonally, checkign for streaks
	streak = 0;
	while ((r >= 0) && (c >= 0)) {
		if (board.at(c).at(r) == turn) {
			streak++;
		}
		else {
			streak = 0;
		}

		if (streak >= 4) {
			return turn;
		}

		r--;
		c--;

	}

	// finding the edge
	r = row; c = col;
	while ((r > 0) && (c < 6)) {
		r--;
		c++;
	}

	// looking for streaks
	streak = 0;
	while ((r <= 6) && (c >= 0)) {
		if (board.at(c).at(r) == turn) {
			streak++;
		}
		else {
			streak = 0;
		}

		if (streak >= 4) {
			return turn;
		}

		r++;
		c--;

	}


	return 0;
}


// used to drop a piece. board is passed by reference and is changed
int dropPiece(vector <vector <int> > &board, const int &dropLocation, const int &turn = 1) {

	int k = 0;
	for (k = 0; k < 7; k++) {
		if (board.at(dropLocation).at(k) == 0) {
			board.at(dropLocation).at(k) = turn;
			break;
		}
	}
	//return 0;
	return checkWin(board, k, dropLocation, turn);
}

void displayBoard(const vector <vector<int> > &board) {

	//system("cls");
	cout << endl << endl << endl;

	// provide column numbers
	for (int k = 0; k < 7; k++) {
		cout << k << " ";
	}
	cout << endl << endl;

	// display board fromm top down
	for (int row = 6; row >= 0; row--) {
		for (int col = 0; col < 7; col++) {
			cout << board.at(col).at(row) << " ";
		}
		cout << endl;
	}
	cout << endl;
}


bool isFull(const vector<vector<int> > board, int dropLocation) {
	if (board.at(dropLocation).at(6) > 0)
		return true;
	else
		return false;
}

