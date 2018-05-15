#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

#include "AI.h"
#include "connect4.h"

using namespace std;



connect4Board interestingSituation() {
	
	connect4Board x;

	x.setTurn(x.computer);

	x.dropPiece(0);
	x.dropPiece(1);
	x.dropPiece(6);
	x.dropPiece(5);
	
	return x;
}


void testingGround(connect4Board board) {

	cout << "original" << endl;
	board.displayBoard();
	system("pause");


	while (true) {	
		
		// get the ai to make a move
		board.setTurn(board.computer);
		
		cout << "calculating next move..." << endl;
		int AI_move = nextMove(board);
		board.dropPiece(AI_move);
		
		board.changeTurn();
		board.displayBoard();
		
		cout << "AI dropped in spot: " << AI_move << endl;
		cout << "where do you want to drop?" << endl;
		
		int player_move;
		cin >> player_move;

		board.dropPiece(player_move);
		board.displayBoard();
	}
	exit(0);

}


int main() {

	connect4Board gameboard = interestingSituation(); // creates interesting situationn
	//dropPiece(gameboard, 0, 1);

	testingGround(gameboard);
	return 0;	
	
	

	int spot_to_drop = -1;
	cout << "Where do you want to drop the next piece?" << endl;
	cin >> spot_to_drop;
	connect4Board game;

	while ((spot_to_drop >= 0) && (spot_to_drop <= 6)) {

		game.changeTurn();

		game.dropPiece(spot_to_drop);
		game.displayBoard();
		int winner = game.checkWin();

		if (winner > 0) {
			cout << winner << " won the game!" << endl;
			break;
		}


		cout << "Where do you want to drop the next piece?" << endl;
		cin >> spot_to_drop;
	}

	
	system("pause");
	return 0;
	
}

