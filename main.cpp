#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>

#include "AI.h"
#include "connect4.h"

using namespace std;

void myPause() {
	string nothing;
	cin.ignore();
	getline(cin, nothing);
}

connect4Board interestingSituation() {
	
	connect4Board x;

	x.setTurn(x.computer);

	x.dropPiece(0);
	x.dropPiece(1);
	x.dropPiece(6);
	x.dropPiece(5);
	
	return x;
}


void demonstration(connect4Board x) {
	connect4Board board = interestingSituation();
	cout << "original" << endl;
	board.displayBoard();
	
	cout << "On this board, 1 is the opponent, 2 is the computer and 0 is an empty space." << endl;
	cout << "It's the computer's turn. If the computer drops a piece in the middle, \nit has two opportunities to connect 4 and the player can only block one of these." << endl;
	cout << "this algorithem succesfully recognizes that there's no escape for the opponent \nif the computer drops in the middle." << endl;
	cout << "Press enter to run the algorithem on the current board" << endl;
	myPause();

	// get the ai to make a move
	board.setTurn(board.computer);
	cout << "calculating next move..." << endl;
	int AI_move = nextMove(board);
	board.dropPiece(AI_move);
		
	board.changeTurn();
	board.displayBoard();
		
	cout << "AI dropped in spot: " << AI_move << endl;
	cout << "where do you want to drop?" << endl;
	cout << "As you can see, there isn't a way out" << endl;

	int player_move;
	cin >> player_move;

	board.dropPiece(player_move);
	board.displayBoard();

	cout << "press enter to have the AI go" << endl;
	myPause();

	AI_move = nextMove(board);
	board.dropPiece(AI_move);
	board.displayBoard();

	cout << "Granted, the odds are stacked against the player in this situation,\nbut it shows how the AI is able to look multiple steps ahead to secure the victory" << endl;
	
	exit(0);

}


void playConnect4(bool AI_is_playing) {
	int spot_to_drop = 0;
	connect4Board game;

	do {
		
		game.changeTurn();
		game.displayBoard();
		cout << "Where do you want to drop the next piece?" << endl;
		cin >> spot_to_drop;
		
		game.dropPiece(spot_to_drop);
		game.displayBoard();
		int winner = game.checkWin();

		// winner holds one of the following: 0,1,2. 0 indicates no winner, 1 indicates player 1 won. 2 indicates the computer or player two won
		if (winner > 0) {
			cout << winner << " won the game!" << endl;
			break;
		}


		game.changeTurn();
		if (AI_is_playing) {
			spot_to_drop = nextMove(game);
		} else {
			cout << "Where do you want to drop the next piece?" << endl;
			cin >> spot_to_drop;
		}
		game.dropPiece(spot_to_drop);
		
	} while ((spot_to_drop >= 0) && (spot_to_drop <= 6) && (game.checkWin() == 0));
}

int main() {

	int userChoice = -1;
	do {
		cout << "what would you like to do?" << endl;
		cout << "[1] Two Player game" << endl;
		cout << "[2] One Player game against my AI" << endl;
		cout << "[3] Demonstration" << endl;
		cin >> userChoice;
	} while (userChoice > 3 || userChoice < 1);

	switch (userChoice) {
	case (1):
		playConnect4(false);
		break;
	case (2):
		playConnect4(true);
		break;
	case(3):
		connect4Board gameboard = interestingSituation(); 
		demonstration(gameboard);
		break;
	}
	
	string userEntered;
	getline(cin, userEntered);
	return 0;
	
}

