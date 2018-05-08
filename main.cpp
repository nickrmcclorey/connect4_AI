#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include "connect4.h"

using namespace std;



vector<vector<int> > interestingSituation() {
	vector <vector <int> > board(7, vector<int>(7, 0));
	connect4Board x;

	int turn = 1;
	x.setTurn(x.player);


	int dropLocations[24] = { 0, 0, 3, 0, 0, 1, 1, 1, 1, 2, 0, 2, 0,  5, 2, 5, 2, 4, 4, 4, 2, 6, 6 };
	
	/*
	for (int k = 0; k < 21; k++) {
		int nothig = dropPiece(board, dropLocations[k], turn);
		turn = changeTurn(turn);
	}
	dropPiece(board, 6, 2);
	dropPiece(board, 3, 2);
	dropPiece(board, 3, 1);
	board.at(2).at(3) = 0;
	board.at(2).at(4) = 0;
	*/
	
	dropPiece(board, 0, 1);
	dropPiece(board, 1, 1);
	dropPiece(board, 6, 1);
	dropPiece(board, 5, 1);
	
	x.dropPiece(0);
	x.dropPiece(1);
	x.dropPiece(6);
	x.dropPiece(5);
	x.displayBoard();
	


	//displayBoard(board);
	
	return board;
}


void testingGround(vector<vector<int> > &board) {

	cout << "original" << endl;
	displayBoard(board);
	system("pause");


	while (1) {
		int AI_move = showCombinations(board);
		system("pause");
		dropPiece(board, AI_move, 2);
		displayBoard(board);
		cout << "AI dropped in spot: " << AI_move << endl;
		cout << "where do you want to drop" << endl;
		int player_move;
		cin >> player_move;
		dropPiece(board, player_move, 1);
		displayBoard(board);
	}
	exit(0);

}


int main() {




	int turn = 1;
	vector <vector <int> > gameboard(7, vector<int>(7, 0));
	gameboard = interestingSituation(); // creates interesting situationn
	//dropPiece(gameboard, 0, 1);


	displayBoard(gameboard);
	testingGround(gameboard);
	return 0;
	
	/*
	testingGround(gameboard);


	int spot_to_drop = 1;
	cout << "Where do you want to dorp the next piece?" << endl;
	cin >> spot_to_drop;
	

	while ((spot_to_drop >= 0) && (spot_to_drop <= 6)) {

		turn = changeTurn(turn);

		// pass by reference!!
		int winner = dropPiece(gameboard, spot_to_drop, turn);
		displayBoard(gameboard);
		
		
		if (winner > 0) {
			cout << winner << " won the game!" << endl;
			break;
		}


		cout << "Where do you want to drop the next piece?" << endl;
		cin >> spot_to_drop;
	}

	
	system("pause");
	return 0;
	*/
}

