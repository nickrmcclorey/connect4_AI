#include <iostream> 
#include <cstdlib>
#include <string>
#include <vector>
#include <cstdio>
#include <fstream>
#include "connect4.h"

using namespace std;



int main() {

	int turn = 1;
	vector <vector <int> > gameboard(7, vector<int>(7, 0));
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
}

