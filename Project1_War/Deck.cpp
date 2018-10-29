#include "Deck.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

Deck::Deck() {
	char ranks[13] = { 'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K' };
	for (int suiteCounter = 0; suiteCounter < 13; suiteCounter++) {
		storage[suiteCounter].setCard(ranks[suiteCounter], 'H');
		storage[suiteCounter + 13].setCard(ranks[suiteCounter], 'D');
		storage[suiteCounter + 13 * 2].setCard(ranks[suiteCounter], 'C');
		storage[suiteCounter + 13 * 3].setCard(ranks[suiteCounter], 'S');
	}
}

void Deck::refreshDeck() {
	cardsRemaining = 52;
}

Card Deck::deal() {
	return storage[--cardsRemaining];
}

void Deck::shuffle() {
	srand(time(0));
	if (cardsRemaining == 52) {
		for (int i = 0; i < 1000; i++) {
			int x = rand() % 52;
			int y = rand() % 52;
			Card temp = storage[x];
			storage[x] = storage[y];
			storage[y] = temp;
		}
	}
	else
		cout << "Cannot shuffle a partial deck!" << endl;
}

int Deck::cardsLeft() {
	return cardsRemaining;
}

void Deck::showDeck() {
	for (int i = cardsRemaining; i >= 0; i--) {
		storage[i].showCard();
	}
}
