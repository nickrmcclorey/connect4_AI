
#ifndef connect4_H
#define connect4_H
using namespace std;

class connect4Board {
private:

	int board[7][6];
	int turn;
	bool gameIsOver;
	int winner;
	int lastX; // x position of last piece dropped
	int lastY; // y position of last piece dropped


public:
	// the three possible pieces on the board
	enum teams { empty, player, computer };
	int checkWin();
	int getTurn();
	void setTurn(int team);
	void changeTurn();
	int at(int x, int y) const;
	bool isFull(int column) const;
	void dropPiece(int column);
	void displayBoard();
	void setAt(int x, int y, int team);
	bool isValidIndex(int, int) const;

	connect4Board() {

		// setting all the spaces on the board to empty
		for (int r = 0; r < 7; r++) {
			for (int c = 0; c < 7; c++) {
				board[r][c] = empty;
			}
		}


		turn = player;
		lastX = -1;
		lastY = -1;
		winner = empty;
		gameIsOver = false;
	}
		

};

//int nextMove(const vector<vector<int> > &board);

//void connect4_AI::runthrough(const vector<vector<int> > &board, const vector<int> &moves);
//bool isGoodMove(vector<vector<int> >board, int turn, const int &length, vector<int> moves);




#endif