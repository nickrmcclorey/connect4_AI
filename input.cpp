#include <iostream>
#include <cstdlib>
#include <sstream>
#include <string>

using namespace std;


int toInt(string num_s) {
	istringstream raw(num_s); // create a stream with number in it
	int toReturn = 0;
	raw >> toReturn; // put the string number into the int variable
	return toReturn; // return int
}

int toInt(char numInChar) {

	// convert char to string
	string toReturn;
	toReturn.push_back(numInChar);
	// use other toInt function to convert string to int and return this
	return toInt(toReturn);
}


string removeSpaces(string copy) {

	for (int k = 0; k < copy.length(); k++) {
		char toCompare = copy.at(k);
		if (toCompare == 32) { // 32 is asc code for space
			copy.erase(k, 1);

			k = 0;
		}

		if ((copy.at(0) == 32) && (copy.length() == 1)) { // 32 is asc code for space
			return "";
		}

	}

	return copy;
}

bool isInt(string input) {
	
	if (input.size() == 0) {
		return false;
	}

	for (int k = 0; k < input.size(); k++) {
		char letter = input.at(k);
		if (letter > '9' || letter < '0')
			return false;
	}
	return true;
}

// used to prevent program from freaking out when user enters 
// string when program wants integer
int askInt(string prompt) {
	string userInput;


	do {
		cout << endl;
		cout << prompt;
		userInput;
		getline(cin, userInput);

		userInput = removeSpaces(userInput);
		if (!isInt(userInput))
			cout << "response wasn't understood. Enter a number" << endl;
		else
			break;

	} while (!isInt(userInput));

	return toInt(userInput);
}

int askInt() {
	return askInt("");
}