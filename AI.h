#ifndef AI_h
#define AI_h
#include "connect4Board.h"

using namespace std;

class connect4_AI {
private:
	// holds all the bad moves
	unordered_set<vector<int> > black;
	// holds all the good moves. 
	vector<vector<int> > gold;

	int friendly;
	int opposing;
	int turnsToLookAhead;

	void runthrough(const connect4Board &board, const vector<int> &moves);

	// adds a series of moves to a list
	void blacklist(const vector<int> &moves);
	void goldlist(const vector<int> &moves);

public:
	int nextMove(connect4Board board);
	


	// checks to see if the blacklist blackContains this combination
	bool blackContains(const vector<int> &moves);
	bool goldContains(const vector<int> &moves); 


	void showBlacklist();
	void showGoldlist(); 

	// looks through the blacklist or goldlist and finds the single moves that are bad
	// so we know what move we should do right now
	vector<int> badSingleMoves();
	vector<int> goodSingleMoves();

	/*
	Extremely important function. This function looks through the blacklist and figures out what moves
	can trap you in a bad situation. If There's no way out of a situation, it blacklists the decision before that
	so the AI doesn't get into that bad situation. It eventually narrrows down the bad moves to a single move */
	void shortenBlacklist();
	void shortenGoldlist(); 

	void setFriendly(int);
	void setOpposing(int);
	void setTurnsToLookAhead(int);

	connect4_AI();
	connect4_AI(int, int, int);

};

// simply check to see if a value is somewhere inside a vector
bool vectorContains(const vector<int> &Array, const int &value);
// this function utilizes the above class to get the next move


#endif