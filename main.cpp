#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include <sstream>
#include <ctime>
#include "AI.h"
#include "connect4Board.h"
#include "input.h"
#include "tester.h"

using namespace std;

void myPause() {
	while (cin) {
		cin.ignore();
	}
	string nothing;
	getline(cin, nothing);
}

void demonstration() {
	connect4_AI ai;
	connect4Board board = interestingSituation(2);
	cout << "original" << endl;
	board.displayBoard();
	
	cout << "On this board, 1 is the opponent, 2 is the computer and 0 is an empty space." << endl;
	cout << "It's the computer's turn. If the computer drops a piece in the middle, \nit has two opportunities to connect 4 and the player can only block one of these." << endl;
	cout << "this algorithem succesfully recognizes that there's no escape for the opponent \nif the computer drops in the middle." << endl;
	cout << "Press enter to run the algorithem on the current board" << endl;
	
	string nothing;
	getline(cin, nothing);

	// get the ai to make a move
	board.setTurn(board.computer);
	cout << "calculating next move..." << endl;
	int AI_move = ai.nextMove(board);
	board.dropPiece(AI_move);
		
	board.changeTurn();
	board.displayBoard();
		
	cout << "AI dropped in spot: " << AI_move << endl;
	cout << "As you can see, there isn't a way out" << endl;
	cout << "where do you want to drop?" << endl;
	cout << "enter the number of the column you want to drop in" << endl;

	int player_move = askInt("enter the number of the column you want to drop in");

	board.dropPiece(player_move);
	board.displayBoard();

	cout << "press enter to have the AI go" << endl;
	getline(cin, nothing);

	AI_move = ai.nextMove(board);
	board.changeTurn();
	board.dropPiece(AI_move);
	board.displayBoard();

	cout << "The AI has won the game" << endl;
	cout << "Granted, the odds are stacked against the player in this situation,\nbut it shows how the AI is able to look multiple steps ahead to secure the victory" << endl;
	cout << "Let's flip the table." << endl;
	cout << "Press enter" << endl;
	
	getline(cin, nothing);

	board = interestingSituation(1);
	board.displayBoard();
	cout << "In order to prevent the player from placing a piece in the middle and winning the game like the AI just did\nthe ai needs to go in the middle gap" << endl;
	cout << "press enter to have the AI go" << endl;
	
	// wait for enter
	getline(cin, nothing);

	AI_move = ai.nextMove(board);
	board.changeTurn();
	board.dropPiece(AI_move);
	board.displayBoard();
	cout << "The AI saw that if it didn't go in the middle gap,\nthere's a way for the player to lock in victory" << endl;
	cout << "where do you want to drop?" << endl;

	exit(0);
}

void advisorMode() {
	cout << "You are represented by 1" << endl;
	cout << "Youre opponent is represented by 2" << endl;

	connect4Board game;
	connect4_AI advisor(1,2,6);
	cout << "are you or your opponent going first?" << endl;
	cout << "[1] you are going first" << endl;
	cout << "[2] your opponent is going first" << endl;

	int firstTurn = askInt("");
	game.setTurn(firstTurn);

	while (true) {
		game.displayBoard();

		if (game.getTurn() == 1) {
			cout << "We suggest you drop in spot " << advisor.nextMove(game) << endl;
			game.dropPiece(askInt("Where will you drop the next piece?"));
			
		} else if (game.getTurn() == 2) {
			game.dropPiece(askInt("Where did your opponent drop?"));
			
		} else {
			cout << "error, turn wasn't changed properly" << endl;
			exit(0);
		}

		if (game.checkWin() != 0) {
			break;
		}

		game.changeTurn();
	}
}

void playConnect4(bool AI_is_playing) {
	int spot_to_drop = 0;
	connect4Board game;
	connect4_AI ai;

	do {
		
		game.changeTurn();
		game.displayBoard();
		cout << "Where do you want to drop the next piece?" << endl;
		spot_to_drop = askInt();
		
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
			spot_to_drop = ai.nextMove(game);
		} else {
			cout << "Where do you want to drop the next piece?" << endl;
			spot_to_drop = askInt();
		}
		game.dropPiece(spot_to_drop);
		
	} while ((spot_to_drop >= 0) && (spot_to_drop <= 6) && (game.checkWin() == 0));
}

void bot_vs_bot() {
	connect4Board game; game.setTurn(1);
	connect4_AI ai1(1, 2, 4);
	connect4_AI ai2(2, 1, 4);

	while (true) {
		game.dropPiece(ai1.nextMove(game));
		if (game.checkWin() > 0) {
			break;
		}
		game.displayBoard();

		game.changeTurn();
		game.dropPiece(ai2.nextMove(game));
		if (game.checkWin() > 0) {
			break;
		}
		game.displayBoard();

		game.changeTurn();
	}

	game.displayBoard();
	cout << game.getTurn() << " won" << endl;

}

void menu() {

	int userChoice = -1;
	do {
		cout << "what would you like to do?" << endl;
		cout << "[1] Two Player game" << endl;
		cout << "[2] One Player game against my AI" << endl;
		cout << "[3] Demonstration" << endl;
		cout << "[4] Bot vs Bot" << endl;
		cout << "[5] Advisor mode" << endl;
		userChoice = askInt();
	} while (userChoice > 5 || userChoice < 1);

	switch (userChoice) {
	case (1):
		playConnect4(false);
		break;
	case (2):
		playConnect4(true);
		break;
	case(3):
		demonstration();
		break;
	case (4):
		bot_vs_bot();
		break;
	case (5):
		advisorMode();
		break;
	}
	myPause();
}

int main() {
	srand(time(0));
	testAI();
	menu();
}
