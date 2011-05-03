// File: DeckOfCards.h
// Declaration of class Deck.

#ifndef DECKOFCARDS_H
#define DECKOFCARDS_H

#include <string>
#include <vector>
using namespace std;

// Card structure definition
struct Card
{
	string face;
	string suit;
	int enumeration;
	bool dealed;
};

// Deck class definition
class DeckOfCards
{
	static const vector< string > suitTypes;
	static const vector< string > faceTypes;
public:
	static const int numberOfCards = 52;
	static const int faces = 13;
	static const int suits = 4;
	DeckOfCards();
	void shuffle();
	void reset();
	Card deal();
	void printDeck() const;
	
private:
	vector< Card > deck;
};

#endif
