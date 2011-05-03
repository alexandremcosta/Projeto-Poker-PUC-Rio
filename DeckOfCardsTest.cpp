// File: DeckOfCardsTest.cpp
// Card shuffling, dealing and reseting program.

#include <iostream>
#include <iomanip>
#include "DeckOfCards.h"
#include "EmptyDeckException.h"

int main()
{
	DeckOfCards deckOfCards;
	deckOfCards.printDeck();
	cout << endl;
	deckOfCards.shuffle();
	deckOfCards.printDeck();
	
	for( int i = 0; i < deckOfCards.numberOfCards + 2; i++ )
	{
		try
		{
			Card card = deckOfCards.deal();
			cout << card.face << "." << card.suit << "\t Dealed: " << ( card.dealed == true ? "true " : "false " )
				<< "\t Enumeration: " << card.enumeration << endl;
		}
		catch( EmptyDeckException &emptyDeckException )
		{
			cout << "Exception occurred: " << emptyDeckException.what() << endl;
		}
	}
	
	deckOfCards.reset();
	deckOfCards.printDeck();	
	return 0;
}
