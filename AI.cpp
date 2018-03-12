#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include "connect4.h"

using namespace std;


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


// 2 indicates good move. 1 indicates bad move. 0 indicates acceptable move
bool isGoodMove(vector<vector<int> >board, int turn, const int &length) {
	
	//cout << "entered isGoodMove alright" << endl;

	// base cases. if other player can immediatly end game, return 0;
	// if length is too big stop searching
	if ((userCanWin(board, turn))) {
		//cout << "base case reached " << endl;
		//system("pause");
		return false;
	}

	if (length >= 4 && turn == 2)
		return false;
	else if (length >= 4 && turn == 1)
		return true;


	int new_turn = changeTurn(turn);
	int userEscapeOptions = 7;
	for (int j = 0; j < 7; j++) {

		//cout << "j = " << j << endl;
		//int can_i_win = 0;
		vector<vector<int> > tempBoard = board;
		if (isFull(tempBoard, j))
			continue;
		else
			dropPiece(tempBoard, j, new_turn); // all possibilities for user

		int new_length = length + 1;
		
		//cout << "about to recur" << endl;
		if (isGoodMove(tempBoard, new_turn, new_length)) {
			userEscapeOptions--;
			//cout << "userEscapeOptions: " << userEscapeOptions << " on level " << length << endl;

		}
	}

	if (userEscapeOptions == 0)
		return true;

}




int nextMove(const vector<vector<int> > &board) {
	

	// looking for good moves to do
	for (int k = 0; k < 7; k++) {
		cout << k << endl;


		if (isFull(board, k))
			continue;


		vector<vector<int> > tempBoard = board;

		// can_i_win_now will hold 2 if he can win
		int can_i_win_now = dropPiece(tempBoard, k, 2);
		if (can_i_win_now > 0)
			return k;


		if (isGoodMove(tempBoard, 1, 0)) {	
			//cout << k << " is a good move" << endl;
			return k;
		}

	}

	//cout << "didn't find good move" << endl;
	
	for (int k = 0; k < 7; k++) {
		if (!isFull(board, k))
			return k;
	}

}// of function



/*
		vector<vector<int> > tempBoard = board;
		// next line will hold 2 or 0
		int winner = dropPiece(tempBoard, k, 1);
		
		if (winner == 1) { // checking to see if move wins game 
			return 2;
		}
		else if (userCanWin(tempBoard) {
			return 1;
		}
		else {
			int nextLength = length + 1;
			int winCount = 0;

			for (int i = 0; i < 7; k++) {
				for (int k = 0; k < 7; k++) {
					int d = isGoodMove(board, nextLength);
					if (d = 2)
						winCount++;
				}
				
				if (winCount == 7)
					return 2;
			
			}
		}
}
	
	// no immediate win was found so
	// check to see if user can win
	
	*/




/*
if this combination wins, goldlist this combination

if this combinattion could loses, blacklist this combination

otherwise append all different user strings and...
	if any of the next choices win, goldlist this combo
	otherwise, if all next choices are bad blacklist this


*/

