#include <iostream>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include "DeckOfCards.h"
#include "Player.h"
#include "InvalidPlayersContainerException.h"
#include "InvalidBetException.h"
a
using namespace std;

// Prototypes
void playOneRound( vector< Player >, DeckOfCards, int );
vector< Player > evaluateHands( vector< Player> );
int takePreFlopBets( vector< Card >, int, int, int );
int takePostFlopBets( vector< Player >, vector< Cards >, int, int );
int nextPlayer( vector< Player >, int );
int takeAmountFrom( Player , int );
string convertInt( int );

// Main
int main( void )
{
	vector< Player > playersContainer;
	DeckOfCards deckOfCards;
	int numberOfPlayers;
	int numberOfRounds;
	
	cout << "How many players on this game? ";
	cin >> numberOfPlayers;
	
	for( int i = 0; i < numberOfPlayers; i++ )
	{
		Player player( "Player_" + convertInt( i ) );
		player.setStack = 100;
		player.setPosition( i );
		playersContainer.push_back( player );
	}
	
	deckOfCards.shuffle();
	
	cout << "How many rounds on this game? ";
	cin >> numberOfRounds
	
	while( --numberOfRounds > 0 )
	{
		playOneRound( playersContainer, deckOfCards );
		
		if( numberOfRounds == 0 )
		{
			cout << "End of game. Do you wanna add more rounds?\n( n <= 0 means no ): ";
			cin >> numberOfRounds;
		}
	}

	return 0;
}

// Private Methods
void playOneRound( vector< Player > playersContainer, DeckOfCards deckOfCards, int smallBlindValue, int bigBlindValue )
{
	int dealerIndex;
	int i, smallBlindIndex, bigBlindIndex;
	vector< Pot > pot; // Main pot + side pots
	vector< Card > tableCards;
	
	if( !(playersContainer.size() > 0 ) ) return;
	
	// Find dealer ( position = 0 ).
	// It assumes that playersContainer is cyclically ordered by players positions.
	// Otherwise it throws an exception.
	dealerIndex = ( playersContainer.size() - playersContainer[ 0 ].getPosition() ) 
							% playersContainer.size();
	if( playersContainer[ dealerIndex ].getPosition() != DEALER )
		throw InvalidPlayersContainerException();

	// Deal cards. Starts dealing from small blind.
	i = smallBlindIndex = ( dealerIndex + 1 ) % playersContainer.size();
	bigBlindIndex = ( smallBlindIndex + 1 ) % playersContainer.size();
	
	do
	{
		Card card1 = deckOfCards.deal();
		Card card2 = deckOfCards.deal();
		vector< Card > hand;
		hand.push_back( card1 );
		hand.push_back( card2 );
		
		playersContainer[ i ].setHand( hand );
		
		i = ( i + 1 ) % playersContainer.size();
	} while( i != smallBlindIndex );
	
	if( playersContainer[ i ].getPosition() != SMALLBLIND ) // Esse cara era pra ser o smallBlind APAGAR ISSO!!!!!!!!!!
		cout << "Inconsistencia no raciocinio: Game.cpp, linha 95" << endl;
		
	// Take pre-flop bets
	takePreFlopBets( playersContainer, pot, dealerIndex, smallBlindValue, bigBlindValue );
	
	// Deal flop	
	tableCards.push_back( deckOfCards.deal() );
	tableCards.push_back( deckOfCards.deal() );
	tableCards.push_back( deckOfCards.deal() );
	
	// Take pre-turn bets
	takePostFlopBets( playersContainer, pot , tableCards, dealerIndex, bigBlindValue );
	
	// Deal turn
	tableCards.push_back( deckOfCards.deal() );
	
	// Take pre-river bets
	takePostFlopBets( playersContainer, pot, tableCards, dealerIndex, bigBlindValue );
	
	// Deal river
	tableCards.push_back( deckOfCards.deal() );
	
	// Take final bets
	takePostFlopBets( playersContainer, pot, tableCards, dealerIndex, bigBlindValue );
	
	// Calculates the winner(s)
	vector< Player > winners = evaluateHands( playersContainer, pot );
	
	// Distributes pots (pot + side pots)
	
}

vector< Player > evaluateHands( vector< Player> playersContainer )
{
	
}

// Returns next playing player
int nextPlayer( vector< Player > playersContainer, int i )
{
	i = ( i + 1 ) % playersContainer.size();
	
	if( playersContainer[ i ].getState() != PLAYING )
		return nextPlayer( playersContainer, i );
	
	return i;
}

int takePreFlopBets( vector< Card > playersContainer, vector< Pot > pot, int dealerIndex, int smallBlindValue, int bigBlindValue )
{
	Pot instantPot; // First pot
	int smallBlindIndex = ( dealerIndex + 1 ) % playersContainer.size();
	int bigBlindIndex = ( smallBlindIndex + 1 ) % playersContainer.size();
	
	// Take blinds
	instantPot.addAmount( smallBlindIndex, takeAmountFrom( playersContainer[ smallBlindIndex ], smallBlindValue ) );
	instantPot.addAmount( bigBlindIndex, takeAmountFrom( playersContainer[ bigBlindIndex ], bigBlindValue ) );
	
	int lastBetValue = bigBlindValue;
	int lastBetterIndex = bigBlindIndex;
	int lastPotPlayerIndex = lastBetterIndex;
	
	// Take bets
	int i = nextPlayer( playersContainer, bigBlindIndex ); // "Under the ground 1": first player to bet
	
	while( i != lastBetterIndex )
	{		
		Player player = playersContainer[ i ];
		int amount = player.calculateBet( lastBetValue, smallBlindValue, bigBlindValue );
		
		if( amount == 0 && ( lastBetValue == bigBlindValue ) )
		{
			if( player.getPosition() != BIGBLIND )
				player.changeState( FOLDED );
		}
		else if( ( amount > player.getStack() ) || ( amount < 0 )  )
				throw InvalidBetException( player.getName() );
			
		instantPot.addAmount( i, takeAmountFrom( player, amount ) );
		
		if( ( player.getStack() == 0 ) && ( player.getState() != ALLIN ) )
		{
			player.changeState( ALLIN );
		}

		if( amount > lastBetValue )
		{
			lastBetterIndex = i;
			lastBetValue = amount;
		}
		
		i = nextPlayer( playersContainer, i );
		
		// Lets big blind player decide last bet
		if( ( playersContainer[ i ].getPosition() == BIGBLIND ) && ( lastBetValue == bigBlindValue ) )
			lastBetterIndex = nextPlayer( playersContainer, lastBetterIndex ); 
	}
	
	
	return pot;
}

int takePostFlopBets( vector< Player > playersContainer, vector< Cards > tableCards, int dealerIndex, int bigBlindValue)
{
	int pot = 0;
	
	int smallBlindIndex = ( dealerIndex + 1 ) % playersContainer.size();
	
	int lastBetValue = 0;
	int lastBetterIndex = dealerIndex;
	
	// Take bets
	int i = smallBlindIndex;
	
	while( i != lastBetterIndex )
	{
		Player player = playersContainer[ i ];
		int amount = player.calculateBet( tableCards, lastBetValue );
		
		pot += takeAmountFrom( player, amount );

		if( amount > lastBetValue )
		{
			lastBetterIndex = i;
			lastBetValue = amount;
		}
			
		i = nextPlayer( playersContainer, i );
	}
	
	return pot;
}

// Take an amount from a player,  and checks and sets whether the player
// is all in or not, and whether the player is folding or not.
int takeAmountFrom( Player player, int amount )
{
	if( amount == 0 )
		player.changeState( FOLDED );
	else if( amount == player.getStack() )
		player.changeState( ALLIN );
	else if( ( amount > player.getStack() ) || ( amount < 0 )  )
			throw InvalidBetException( player.getName() );
		
	player.decreaseStack( amount );
	return amount;	
}

string convertInt(int number)
{
   stringstream ss;
   ss << number;
   return ss.str();
}
