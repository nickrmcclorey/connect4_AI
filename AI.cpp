#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include "connect4.h"

using namespace std;


bool userCanWin(const vector<vector<int> > &board) {

	for (int k = 0; k < 7; k++) {
		vector<vector<int> > tempBoard = board;
		int winner = dropPiece(tempBoard, k, 1);
		if (winner == 1)
			return true;
		
	}
	// if no possible wins are found return false
	return false;
}


// 2 indicates good move. 1 indicates bad move. 0 indicates acceptable move
int isGoodMove(vector<vector<int> >board,int lastDro int length) {
	
	if (moves.size() >= 2)
		return 0;

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
	



int nextMove(const vector<vector<int> > &board) {
	
	// looking for good moves to do
	for (int k = 0; k < 7; k++) {
		vector<vector<int> > tempBoard = board;
		dropPiece(tempBoard, k, 2);
		int status == isGoodMove(tempBoard, 0);
		if (status == 1) {
			continue;
		}
		else if (status == 2) {
			return k;
		}
	}

	// no great moves found so settle with okay move
	for (int k = 0; k < 7; k++) {
		vector<vector<int> > tempBoard = board;
		dropPiece(tempBoard, k, 2);
		int status == isGoodMove(tempBoard, 0);
		if (status == 1) {
			continue;
		}
		else if (status == 0) {
			return k;
		}
	}

}



/*
if this combination wins, goldlist this combination

if this combinattion could loses, blacklist this combination

otherwise append all different user strings and...
	if any of the next choices win, goldlist this combo
	otherwise, if all next choices are bad blacklist this


*/

