#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>

#include "connect4Board.h"
#include "AI.h"
#include "input.h"

using namespace std;


void connect4_AI::setFriendly(int input) {
	friendly = input;
}

void connect4_AI::setOpposing(int input) {
	opposing = input;
}

void connect4_AI::setTurnsToLookAhead(int input) {
	turnsToLookAhead = input;
}

connect4_AI::connect4_AI() {
	friendly = connect4Board::computer;
	opposing = connect4Board::player;
	turnsToLookAhead = 6;
}

connect4_AI::connect4_AI(int Friend, int Opposing, int turnsAhead) {
	this->friendly = Friend;
	this->opposing = Opposing;
	this->turnsToLookAhead = turnsAhead;
}

int connect4_AI::nextMove(connect4Board board) {
	gold.clear();
	black.clear();

	//empty moveset
	vector<int> nothing;
	connect4_AI AI_man;

	// this next line done because the function will change the 
	// turn each time, so it will be switched back immediately
	board.setTurn(board.player);
	// exploring all possibilities, taking note of good and bad possibilities
	AI_man.runthrough(board, nothing);
	
	// making deductions based on bad move sets
	AI_man.shortenBlacklist();
	AI_man.shortenGoldlist();
	

	vector<int> goodMoves = AI_man.goodSingleMoves();
	if (goodMoves.size() > 0) {
		return goodMoves.at(0);
	}

	vector <int> badMoves = AI_man.badSingleMoves();
	// get a list of moves that aren't bad
	for (int k = 0; k < 7; k++) {
		if (!vectorContains(badMoves, k) && !board.isFull(k))
			goodMoves.push_back(k);

	}

	//srand(time(0));
	if (goodMoves.size() > 0) {
		int goodMoveIndex = rand() % goodMoves.size();
		return goodMoves.at(goodMoveIndex);
	} else {
		return rand() % 7;
	}



}


void connect4_AI::blacklist(const vector<int> &moves) {
	black.push_back(moves);
}

bool connect4_AI::blackContains(const vector<int> &moves) {
	for (int k = 0; k < black.size(); k++) {
		if (black.at(k) == moves)
			return true;
	}
	return false;
}

void connect4_AI::showBlacklist() {
	cout << "blacklist:" << endl;
	for (int k = 0; k < black.size(); k++) {
		for (int i = 0; i < black.at(k).size(); i++) {
			cout << black.at(k).at(i);
		}
		cout << endl;
	}

}

vector<vector<int> > removeDups(vector<vector<int> > array) {
	vector<vector<int> > noDups(0);

	for (int k = 0; k < array.size(); k++) {

		bool duplicate = false;

		vector<int> entry = array.at(k);
		for (int i = 0; i < k; i++) { // inner loop checks for duplicates
			if (entry == array.at(i)) {
				duplicate = true;
			}
		}

		if (!duplicate) {
			noDups.push_back(array.at(k));
		}

	}

	// This is just to keep the compiler happy
	return noDups;
}

bool containsRoot(const vector<int> &base, const vector<int> &extension) {
	for (int k = 0; k < base.size() && k < extension.size()	; k++) {
		if (base.at(k) != extension.at(k)) {
			return false;
		}
	}
	return true;
}

bool areSiblings(const vector<int> &vec1, const vector<int> &vec2) {
	if (vec1.size() != vec2.size()) {
		return false;
	}

	for (int k = 0; k < vec1.size() - 1; k++) {
		if (vec1.at(k) != vec2.at(k)) {
			return false;
		}
	}
	return true;
}

void connect4_AI::shortenBlacklist() {
	for (int k = 0; k < black.size(); k++) {
		if (black.at(k).size() % 2 == 0) {
			black.at(k).pop_back();
		}
	}



	for (int k = 0; k < black.size(); k++) {
		// used to skip some repeating values in the blacklist
		if ((k > 0) && (black.at(k) == black.at(k - 1) || areSiblings(black.at(k),black.at(k-1)))) {
			continue;
		}

		vector<int> baseMoves = black.at(k);

		int escapeOptions = 7;
		for (int i = 0; i < 7; i++) {

			baseMoves.back() = i;

			if (this->blackContains(baseMoves)) {
				escapeOptions--;
			} else {
				break;
			}

		}

		if (escapeOptions == 0) {
			baseMoves.pop_back();
			baseMoves.pop_back();

			if (black.back() != baseMoves)
				this->blacklist(baseMoves);
		}



	}

	black = removeDups(black);

}

vector<int> connect4_AI::badSingleMoves() {
	vector<int> badMoves;

	for (int k = 0; k < black.size(); k++) {
		if (black.at(k).size() == 1)
			badMoves.push_back(black.at(k).at(0));
	}

	return badMoves;
}


void connect4_AI::goldlist(const vector<int> &moves) {
	gold.push_back(moves);
}

bool connect4_AI::goldContains(const vector<int> &moves) {
	
	for (int k = 0; k < gold.size(); k++) {
		if (gold.at(k) == moves)
			return true;
	}
	// at this point, the combination has not been found
	return false;
}

vector<int> connect4_AI::goodSingleMoves() {
	vector<int> goodMoves;

	for (int k = 0; k < gold.size(); k++) {
		if (gold.at(k).size() == 1)
			goodMoves.push_back(gold.at(k).at(0));
	}

	return goodMoves;
}

void connect4_AI::showGoldlist() {
	cout << "Goldlist:" << endl;

	for (int k = 0; k < gold.size(); k++) {
		for (int i = 0; i < gold.at(k).size(); i++) {
			cout << gold.at(k).at(i);
		}
		cout << endl;
	}
}

void connect4_AI::shortenGoldlist() {

	for (int k = 0; k < gold.size(); k++) {
		if (gold.at(k).size() % 2 == 1 && gold.at(k).size() > 1) {
			gold.at(k).pop_back();
		}
	}

	for (int k = 0; k < gold.size(); k++) {
		if (gold.at(k).size() <= 1) {
			break;
		}
		
		vector<int> modified = gold.at(k);
		
		int escapeOptions = 7;
		for (int i = 0; i < 7; i++) {

			modified.back() = i;

			if (goldContains(modified)) {
				escapeOptions--;
			} else {
				break;
			}

		}
		if (escapeOptions == 0 && modified.size() > 1) {
			modified.pop_back();
			this->goldlist(modified);
		}


	}
}


/*
Important function. It is a recursive function that looks through all the possible combination of moves for the 
next couple moves. How far it looks ahead is determined by the number in the first if statement. It isn't 
possible to look for all combinations due to processing limitations. Increase this number to increase
how far the AI looks ahead and increase execution time. Shorten it to quicken execution time. Always have it as even
as its looking for losing combbinations and even moves are player moves
*/
void connect4_AI::runthrough(const connect4Board &board, const vector<int> &moves) {


	if (moves.size() >= turnsToLookAhead) // keeps execution time low
		return;


	for (int k = 0; k < 7; k++) {

		// checks to see if board is full in which case, a piece can't be dropped there
		if (board.isFull(k)) {
			continue;
		}

		// temporary board is set to original board and then changed to look at all combinations
		connect4Board tempBoard = board;
		tempBoard.changeTurn();
		vector<int> tempMoves = moves;
		tempMoves.push_back(k);

		// returns 2 if AI won and returns 1 if player won. Returns 0 if no one won
		//int winner = dropPiece(tempBoard,k,turn);
		tempBoard.dropPiece(k);
		int winner = tempBoard.checkWin();
		
		if (winner == opposing) {
			this->blacklist(tempMoves);
			break;
		} else if (winner == friendly) {
			this->goldlist(tempMoves);
			break;
		} else {
			runthrough(tempBoard, tempMoves);// runs this function again
		}


	}

}

bool vectorContains(const vector<int> &Array, const int &value) {

	for (int k = 0; k < Array.size(); k++) { // cycles through array
		if (Array.at(k) == value) { // checks to see if value exists
			return true;
		}
	}
	return false; // if program gets to this point, no match has been foundd
}





