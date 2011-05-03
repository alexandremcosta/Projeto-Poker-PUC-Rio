// File: DeckOfCardsTest.cpp
// Card shuffling, dealing and reseting program.

#include <iostream>
#include <iomanip>
#include "DeckOfCards.h"
#include "Player.h"
#include <stdexcept>

int main()
{
	Player player( "Alexandre" );
	cout << "Tentativa 1:\n" << player.getName() << "\nStack: " << player.getStack() << "\nPosition: " << player.getPosition() << "\n";
	try
	{
		cout << "Tentativa de bet: " << player.calculateBet();
	}
	catch( logic_error &exception )
	{
		cout << "Exception occurred: " << exception.what() << endl;
	}
	cout << "\n";
	
	cout << "Tentativa2:\nAtribuindo valores errados as variaveis de "<< player.getName() << "...\n";
	try
	{
		player.setStack( -500 );
		player.setPosition( -2 );
	}
	catch( logic_error &exception )
	{
		cout << "Exception occurred: " << exception.what() << endl;
	}
	cout << player.getName() << "\nStack: " << player.getStack() << "\nPosition: " << player.getPosition() << "\n";
	try
	{
		cout << "Tentativa de bet: " << player.calculateBet();
	}
	catch( logic_error &exception )
	{
		cout << "Exception occurred: " << exception.what() << endl;
	}
	cout << "\n";
	
	cout << "Tentativa3:\nAtribuindo valores corretos as variaveis de "<< player.getName() << "...\n";
	try
	{
		player.setStack( 500 );
		player.setPosition( 2 );
	}
	catch( logic_error &exception )
	{
		cout << "Exception occurred: " << exception.what() << endl;
	}
	cout << player.getName() << "\nStack: " << player.getStack() << "\nPosition: " << player.getPosition() << "\n";
	try
	{
		cout << "Tentativa de bet: " << player.calculateBet();
	}
	catch( logic_error &exception )
	{
		cout << "Exception occurred: " << exception.what() << endl;
	}
	cout << "\n";
	
	return 0;
}
/*
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
			cout << card.face << " of " << card.suit << " - Dealed: " << ( card.dealed == true ? "true " : "false " )
				<< " - Priority: " << card.priority << endl;
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
*/
