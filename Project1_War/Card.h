#ifndef CARD_H
#define CARD_H

class Card {
private:
	char rank;
	char suite;
public:
	Card();
	Card(char, char);
	void setCard(char, char);
	int getValue();
	void showCard();

	/* Additional Methods */
	void getRankString();
	void getSuiteString();
};
#endif 