#ifndef DECK_H
#define DECK_H
#include "Card.h"
class Deck {
private:
	Card storage[52];
	int cardsRemaining = 52;
public:
	Deck();
	void refreshDeck();
	Card deal();
	void shuffle();
	int cardsLeft();
	void showDeck();
};
#endif