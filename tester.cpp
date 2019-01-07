#include <iostream>
#include <cstdlib>
#include <vector>

#include "AI.h"
#include "connect4Board.h"
#include "tester.h"

using namespace std;

connect4Board interestingSituation(int team) {

	connect4Board x;

	x.setTurn(team);

	x.dropPiece(0);
	x.dropPiece(1);
	x.dropPiece(6);
	x.dropPiece(5);

	return x;
}

void testFailed() {
	cout << "test failed" << endl;
	exit(0);
}

void testAI() {
	connect4Board game = interestingSituation(2); game.setTurn(game.computer);
	connect4_AI ai;

	cout << ai.nextMove(game) << endl;;

	if (ai.nextMove(game) != 3) {
		testFailed();
	}

	game.dropPiece(3);

	game.changeTurn();
	game.dropPiece(2);
	game.changeTurn();

	if (ai.nextMove(game) != 4) {
		testFailed();
	}
}