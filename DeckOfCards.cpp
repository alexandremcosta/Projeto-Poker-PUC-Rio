// File: DeckOfCards.cpp
// Defines a 52 standard card deck, using 4x13 matrix.

#include <cstdlib> // prototypes for rand and srand
#include <ctime> // prototype for time
#include <iostream>
#include <iomanip>
#include "DeckOfCards.h"
#include "EmptyDeckException.h"
using namespace std;


// Constructor
DeckOfCards::DeckOfCards()
	: deck( numberOfCards )
{	
	reset(); 			// sets values for a poker deck
	srand( time(0) ); 	// seed random number generator
}

//Methods
void DeckOfCards::shuffle()
{
	// shuffle cards randomly 10 times
	for( int round = 0; round < 10; round++ )
	{
		for( int i = 0; i < numberOfCards; i++ )
		{
			int j = rand() % numberOfCards;
			Card temp = deck[ i ];
			deck[ i ] = deck[ j ];
			deck[ j ] = temp;
		}
	}
}

void DeckOfCards::reset()
{
	const string suit[ suits ] = { "Clubs", "Diamonds", "Hearts", "Spades" };
	const string face[ faces ] = { "Deuce", "Three", "Four", "Five", 
										"Six", "Seven", "Eight", "Nine", 
										"Ten", "Jack",  "Queen", "King", "Ace"	};
	// resets values for a poker deck
	for( int i = 0; i < numberOfCards; i++ )
	{
		deck[ i ].suit = suit[ i / faces ];
		deck[ i ].face = face[ i % faces ];
		deck[ i ].enumeration = ( ( i % 13 ) * 4 ) + ( i / 13 ) + 1; //Example: 2c = 1, 3d = 6, 4h = 11, As = 52
		deck[ i ].dealed = false;
	}
}

Card DeckOfCards::deal()
{	
	int i;
	
	for( i = 0; ( i < numberOfCards && deck[ i ].dealed == true ) ; i++ );
	
	if( !(i < numberOfCards) ) // No cards available
		throw EmptyDeckException();
	
	deck[ i ].dealed = true;
	
	return deck[ i ];
}

void DeckOfCards::printDeck() const
{
	for( int i = 0; i < numberOfCards; i++ )
		cout << right << setw( 5 ) << deck[ i ].face << " of " 
			<< left << setw( 8 ) << deck[ i ].suit << ( ( i + 1 ) % 2 ? '\t' : '\n' );
}
