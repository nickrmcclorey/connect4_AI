#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>
#include "connect4.h"

using namespace std;

class connect4_AI {
public:
	void runthrough(const connect4Board &board, const vector<int> &moves);

	// holds all the bad moves
	vector<vector<int> > black;
	// holds all the good moves. not being used yet
	vector<vector<int> > gold;
	

	// adds a series of moves to the blacklist
	void blacklist(const vector<int> &moves) {
		black.push_back(moves);
	}

	// checks to see if the blacklist contains this combination
	bool contains(vector<int> moves) {
		for (int k = 0; k < black.size(); k++) {
			if (black.at(k) == moves)
				return true;
		}
		return false;
	}

	// blacklists the moves leading up to a certain set of moves
	void blacklistRoot(vector<int> moves) {
		moves.pop_back();
		black.push_back(moves);
	}

	// displays all the bad moves
	void showBlacklist() {
		cout << "blacklist:" << endl;
		for (int k = 0; k < black.size(); k++) {
			for (int i = 0; i < black.at(k).size(); i++) {
				cout << black.at(k).at(i);
			}
			cout << endl;
		}

	}
	
	// adds a combination to the goldlist
	void goldlist(vector<int> moves) {
		gold.push_back(moves);
	}

	void goldlistRoot(vector<int> moves) {
		moves.pop_back();
		gold.push_back(moves);
	}

	// looks through the blacklist and find the single moves that are bad
	// so we know what move we shoudl do know
	vector<int> badSingleMoves (){
		vector<int> badMoves;
		
		for (int k = 0; k < black.size(); k++) {
			if (black.at(k).size() == 1)
				badMoves.push_back(black.at(k).at(0));
		}

		return badMoves;
	}


	/*
	Extremely important function. This function looks through the blacklist and figures out what moves
	can trap you in a bad situation. If There's no way out of a situation, it blacklists the decision before that
	so the AI doesn't get into that bad situation. It eventually narrrows down the bad moves to a single move
	*/
	void shortenBlacklist() {
		for (int k = 0; k < black.size(); k++) {
			if (black.at(k).size() % 2 == 0) {
				black.at(k).pop_back();
			}
		}



			for (int k = 0; k < black.size(); k++) {
				if ((k > 0) && (black.at(k) == black.at(k - 1))) {
					continue;
				}

				vector<int> baseMoves = black.at(k);

				int escapeOptions = 7;
				for (int i = 0; i < 7; i++) {
					
					//baseMoves.pop_back();
					//baseMoves.push_back(i);
					baseMoves.back() = i;

					if (this->contains(baseMoves)) {
						escapeOptions--;
					}

				}

				if (escapeOptions == 0) {
					baseMoves.pop_back();
					baseMoves.pop_back();
					//black.at(k) = baseMoves;
					if (black.back() != baseMoves)
						this->blacklist(baseMoves);
				}

				
			
			}

		
	}

};

//connect4_AI file;



/*
Important function. It is a recursive function that looks through all the possible combination of moves for the 
next couple moves. How far it looks ahead is determined by the number in the first if statement. It isn't 
possible to look for all combinations due to processing limitations. Increase this number to increase
how far the AI looks ahead and increase execution time. Shorten it to quicken execution time. Always have it as even
as its looking for losing combbinations and even moves are player moves
*/
void connect4_AI::runthrough(const connect4Board &board, const vector<int> &moves) {


	if (moves.size() >= 4) // keeps execution time low
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
		
		if (winner == tempBoard.player) {
			this->blacklist(tempMoves);
		} else if (winner == 2) {
			this->goldlist(moves);
		} else {
			runthrough(tempBoard, tempMoves);// runs this function again
		}


	}

}

bool contains(vector<int> Array, int value) {

	for (int k = 0; k < Array.size(); k++) { // cycles through array
		if (Array.at(k) == value) { // checks to see if value exists
			return true;
		}
	}
	return false; // if program gets to this point, no match has been foundd
}

int showCombinations(connect4Board board) {
	
	//empty moveset
	vector<int> nothing;
	connect4_AI AI_man;
	board.setTurn(board.player);
	AI_man.runthrough(board, nothing);
	AI_man.shortenBlacklist();
	

	vector<int> goodMoves;
	vector <int> badMoves = AI_man.badSingleMoves();
	for (int k = 0; k < 7; k++) {
		if (!contains(badMoves, k))
			goodMoves.push_back(k);

	}

	srand(time(0));
	int goodMoveIndex = rand() % goodMoves.size();
	return goodMoves.at(goodMoveIndex);

}


bool userCanWin(const vector<vector<int> > &board, int turn) {

	for (int k = 0; k < 7; k++) {

		if (isFull(board,k))
			continue;

		vector<vector<int> > tempBoard = board;
		int winner = dropPiece(tempBoard, k, turn);
		
		if (winner == turn)
			return true;
		
	}
	// if no possible wins are found return false
	return false;
}

