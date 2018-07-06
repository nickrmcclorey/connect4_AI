#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

#include "input.h"
#include "connect4Board.h"

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

bool connect4Board::isFull(int column) const {
	if (this->at(column, 5) != empty) {
		return true;
	} else {
		return false;
	}
}

bool connect4Board::isValidIndex(int x, int y) const {
	if ((x > 6) || (y > 5) || (x < 0) || (y < 0)) {
		return false;
	} else {
		return true;
	}
}

int connect4Board::at(int x, int y) const {
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
	for (int k = 0; k < 6; k++) {

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
	while ((r < 5) && (c < 6)) {
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
	while ((r <= 5) && (c >= 0)) {
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
	
	for (int k = 5; k >= 0; k--) {
		if (this->at(dropLocation, k) != empty) {
			this->setAt(dropLocation, k+1, turn);
			lastX = dropLocation;
			lastY = k+1;
			return;
		}
	}
	
	this->setAt(dropLocation, 0, turn);
	lastX = dropLocation;
	lastY = 0;
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
	for (int row = 5; row >= 0; row--) {
		for (int col = 0; col < 7; col++) {
			cout << this->at(col, row) << " ";
		}
		cout << endl;
	}
	cout << endl;
}




