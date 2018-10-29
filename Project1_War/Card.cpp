#include "Card.h"
#include <iostream>
using namespace std;

Card::Card() {
	rank = 'z';
	suite = 'z';
}

Card::Card(char r, char s) {
	rank = r;
	suite = s;
}

void Card::setCard(char r, char s) {
	rank = r;
	suite = s;
}

int Card::getValue() {
	int value = 0;
	switch (rank) {
	case 'A': value = 1; break;
	case '2': value = 2; break;
	case '3': value = 3; break;
	case '4': value = 4; break;
	case '5': value = 5; break;
	case '6': value = 6; break;
	case '7': value = 7; break;
	case '8': value = 8; break;
	case '9': value = 9; break;
	case 'T': value = 10; break;
	case 'J': value = 11; break;
	case 'Q': value = 12; break;
	case 'K': value = 13; break;
	}
	return value;
}

void Card::showCard() {
	//char mySuite = getSuite();
	//char myRank = getRank();

	char mySuite = suite;
	char myRank = rank;
	//cout << mySuite << " " << myRank << endl;

	// Hearts
	if (suite == 'H') {
		getRankString(); getSuiteString();
		cout << "	 _______ " << endl;
		if(rank == 'T')
			cout << "	|10     |" << endl;
		else
			cout << "	|" << rank << "      |" << endl;
		cout << "	|       |" << endl;
		cout << "	| __ __ |" << endl;
		cout << "	|(  Y  )|" << endl;
		cout << "	| \\   / |" << endl;
		cout << "	|  \\ /  |" << endl;
		cout << "	|   V   |" << endl;
		if(rank == 'T')
			cout << "	|     10|" << endl;
		else
			cout << "	|      " << rank << "|" << endl;
		cout << "	'-------'" << endl;
	}

	// Diamonds
	else if (suite == 'D') {
		getRankString(); getSuiteString();
		cout << "	.-------." << endl;
		if (rank == 'T')
			cout << "	|10     |" << endl;
		else
			cout << "	|" << rank << "      |" << endl;
		cout << "	|   ^   |" << endl;
		cout << "	|  / \\  |" << endl;
		cout << "	| /   \\ |" << endl;
		cout << "	| \\   / |" << endl;
		cout << "	|  \\ /  |" << endl;
		cout << "	|   V   |" << endl;
		if (rank == 'T')
			cout << "	|     10|" << endl;
		else
			cout << "	|      " << rank << "|" << endl;
		cout << "	'-------'" << endl;
	}

	// Clubs
	else if (suite == 'C') {
		getRankString(); getSuiteString();
		cout << "	.-------." << endl;
		if (rank == 'T')
			cout << "	|10     |" << endl;
		else
			cout << "	|" << rank << "      |" << endl;
		cout << "	|       |" << endl;
		cout << "	|   _   |" << endl;
		cout << "	|  ( )  |" << endl;
		cout << "	| (_Y_) |" << endl;
		cout << "	|   ^   |" << endl;
		cout << "	|       |" << endl;
		if (rank == 'T')
			cout << "	|     10|" << endl;
		else
			cout << "	|      " << rank << "|" << endl;
		cout << "	'-------'" << endl;
	}

	// Spades
	else if (suite == 'S') {
		getRankString(); getSuiteString();
		cout << "	.-------." << endl;
		if (rank == 'T')
			cout << "	|10     |" << endl;
		else
			cout << "	|" << rank << "      |" << endl;
		cout << "	|   ^   |" << endl;
		cout << "	|  / \\  |" << endl;
		cout << "	| /   \\ |" << endl;
		cout << "	|(_/^\\_)|" << endl;
		cout << "	|  /_\\  |" << endl;
		cout << "	|       |" << endl;
		if (rank == 'T')
			cout << "	|     10|" << endl;
		else
			cout << "	|      " << rank << "|" << endl;
		cout << "	'-------'" << endl;
	}
}

/* Additional Methods */
void Card::getRankString() {
	switch (rank) {
	case 'A': cout << "      Ace of "; break;
	case '2': cout << "      Two of "; break;
	case '3': cout << "      Three of "; break;
	case '4': cout << "      Four of "; break;
	case '5': cout << "      Five of "; break;
	case '6': cout << "      Six of "; break;
	case '7': cout << "      Seven of "; break;
	case '8': cout << "      Eight of "; break;
	case '9': cout << "      Nine of "; break;
	case 'T': cout << "      Ten of "; break;
	case 'J': cout << "      Jack of "; break;
	case 'Q': cout << "      Queen of "; break;
	case 'K': cout << "      King of "; break;
	}
}

void Card::getSuiteString() {
	switch (suite) {
	case 'H': cout << "Hearts" << endl; break;
	case 'C': cout << "Clubs" << endl; break;
	case 'S': cout << "Spades" << endl; break;
	case 'D': cout << "Diamonds" << endl; break;
	}
}
