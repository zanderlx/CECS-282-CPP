// Lexzander Saplan - 014177252
// Project 1 - War
// CECS 282 - Steve Gold
// September 20, 2017
#include "Deck.h"
#include "Card.h"
#include <string>
#include <iostream>
using namespace std;

int main()
{
	cout << "Get ready to play WAR!!!" << endl;

	Deck myDeck;
	Card card1;
	Card card2;
	bool playAgain = false;
	string userChoice;
	int menuChoice;

	while (!playAgain) {
		cout << "1) Get a new card deck" << endl;
		cout << "2) Show all remaining cards in the deck" << endl;
		cout << "3) Shuffle" << endl;
		cout << "4) Play WAR!" << endl;
		cout << "5) Exit" << endl;

		cin >> menuChoice;
		if (menuChoice == 1) {
			cout << endl << "...deck refreshed..." << endl;
			myDeck.refreshDeck();
		}
		else if (menuChoice == 2) {
			cout << endl << "...showing available cards..." << endl;
			myDeck.showDeck();
		}
		else if (menuChoice == 3) {
			if (myDeck.cardsLeft() == 52) {
				cout << endl <<  "...deck shuffled..." << endl;
				myDeck.shuffle();
			}
			else
				cout << endl << "Cannot shuffle in the middle of a game!" << endl;
		}
		else if (menuChoice == 4) {
			if (myDeck.cardsLeft() > 0) {
				cout << endl << "There are currently " << myDeck.cardsLeft() << " cards in the deck." << endl;
				cout << "...dealing..." << endl;

				card1 = myDeck.deal();
				card2 = myDeck.deal();

				cout << "One for you..." << endl;
				card1.showCard();
				cout << "One for me..." << endl;
				card2.showCard();

				if (card1.getValue() > card2.getValue())
					cout << endl << "You Win!!!" << endl;
				else if (card1.getValue() < card2.getValue())
					cout << endl << "I Win!!!" << endl;
				else if (card1.getValue() == card2.getValue())
					cout << "It's A Tie!!!" << endl;
				cout << endl << "There are " << myDeck.cardsLeft() << " cards remaining in the deck." << endl;
			}
			else {
				cout << "There are " << myDeck.cardsLeft() << " cards in the deck." << endl;
				cout << "Not enough cards in the deck to play again! Want to refresh the deck to play again? (Yes or No)";
				cin >> userChoice;
				if (userChoice == "yes" || userChoice == "yes") {
					cout << endl << "Deck Refreshed!" << endl;
					myDeck.refreshDeck();
				}
				else
					break;
			}
		}
		else if (menuChoice == 5)
			break;
	}

	cout << endl << "Goodbye" << endl << endl;
	system("pause");
	return 0;
}