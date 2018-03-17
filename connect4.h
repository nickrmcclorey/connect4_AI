
#ifndef connect4_H
#define connect4_H
using namespace std;

// from game_manager
int changeTurn(const int &currentTurn);
int checkWin(const vector<vector<int> > &board, const int &row, const int &col, const int &turn);
int dropPiece(vector <vector <int> > &board, const int &dropLocation, const int &turn);
void displayBoard(const vector <vector<int> > &board);
bool isFull(const vector<vector<int> > board, int dropLocation);



// from AI.cpp
bool userCanWin(const vector<vector<int> > &board, int turn);
int nextMove(const vector<vector<int> > &board);
void showCombinations(const vector<vector<int> > board);
void runthrough(const vector<vector<int> > &board, vector<int> moves);
bool isGoodMove(vector<vector<int> >board, int turn, const int &length, vector<int> moves);


#endif