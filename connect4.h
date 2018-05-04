
#ifndef connect4_H
#define connect4_H
using namespace std;

// from game_manager
int changeTurn();
int checkWin(const vector<vector<int> > &board, const int &row, const int &col, const int &turn);
int dropPiece(vector <vector <int> > &board, const int &dropLocation, const int &turn);
void displayBoard(const vector <vector<int> > &board);
bool isFull(const vector<vector<int> > board, int dropLocation);



// from AI.cpp
bool userCanWin(const vector<vector<int> > &board, int turn);
//int nextMove(const vector<vector<int> > &board);
int showCombinations(const vector<vector<int> > board);
void runthrough(const vector<vector<int> > &board, const vector<int> &moves);
//bool isGoodMove(vector<vector<int> >board, int turn, const int &length, vector<int> moves);


class connect4Board {
private:

	int board[7][7];
	int turn;
	bool gameIsOver;
	int lastX; // x position of last piece dropped
	int lastY; // y position of last piece dropped


public:
	enum teams { empty, player, computer };
	int checkWin();

	int getTurn();
	void setTurn(int team);
	void changeTurn();
	int at(int x, int y);
	bool isFull(int column);
	void dropPiece(int column);
	void displayBoard();
	void setAt(int x, int y, int team);
	bool isValidIndex(int, int);

};


#endif