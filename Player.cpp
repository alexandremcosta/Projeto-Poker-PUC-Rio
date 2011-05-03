// File: Player.cpp
// Defines a player behavior.

#include <cstdlib> // prototypes for rand and srand
#include <ctime> // prototype for time
#include <string>
#include <cmath>
#include "Player.h"
#include "InvalidHandException.h"
#include "InvalidNewNameException.h"
#include "InvalidStackException.h"
#include "InvalidPositionException.h"
#include "NoStackException.h"

using namespace std;

// Constructor
Player::Player( string newName )
{	
	setName( newName );
	setPosition( 0 );
	setStack( 0 );
	setStatePlaying();
    srand( time(0) );   // seed random number generator
}

// Private Methods
void setName( string newName )
{
	if( newName.length() == 0 )
		throw InvalidNewNameException();
	
	name = newName;
}

// Public Methods

string Player::getName()
{
	return name;
}

int Player::calculateBet( int lastBetValue, int smallBlindValue, int bigBlindValue ); // Before flop
{
	int pos = getPosition();

	int decision = rand() % 3; // 0: fold; 1: check; 2: raise;
	
	if( decision == 0 )
		return 0;
	else if( decision == 1 )
	{
		if( pos == SMALLBLIND )
		{
			return ( ( bigBlindValue - smallBlindValue ) < stack ? ( bigBlindValue - smallBlindValue ) : stack );
		}
		else if( pos == BIGBLIND )
		{
			return 0;
		}
		else if( lastBetValue < stack )
			return lastBetValue;
		else
		{
			return stack; // All in
		}
	}
	else
	{
		if( lastBetValue < stack )
			return ( ( rand() % ( stack - lastBetValue ) ) + lastBetValue );
		else
		{
			return stack; // All in
		}
	}
	
	cout << "Erro na calculate bet" << endl; // Apagar isso!!!!!!!!!!!!!!!!!!!!!
	
	return 0;	
}

int Player::calculateBet( vector< Card > tableCards, int lastBetValue ) // After flop
{
	int decision = rand() % 3; // 0: fold; 1: same bet as the last one; 2: raise;
	if( decision == 0 )
		return 0;
	else if( decision == 1 )
	{
		if( lastBetValue < stack )
			return lastBetValue;
		else
		{
			return stack; // All in
		}
	}
	else
	{
		if( lastBetValue < stack )
			return ( ( rand() % ( stack - lastBetValue ) ) + lastBetValue );
		else
		{
			return stack; // All in
		}
	}
	
	cout << "Erro na calculate bet" << endl; // Apagar isso!!!!!!!!!!!!!!!!!!!!!
	
	return 0;	
}

void Player::setStack( int newStack )
{
	if( newStack < 0 )
		throw InvalidStackException( name );
	
	stack = newStack;
}

int Player::getStack()
{	
	return stack;
}

void Player::increaseStack( int amount )
{
	if( amount + stack < 0 )
		throw InvalidStackException( name );
	
	stack += amount;
}

void Player::decreaseStack( int amount )
{
	if( stack - amount < 0 )
		throw InvalidStackException( name );
	
	stack -= amount;
}

void Player::setPosition( int newPosition )
{
	if( newPosition < 0 )
		throw InvalidPositionException( name );
	
	position = newPosition;
}

int Player::getPosition()
{
	return position;	
}

void Player::setHand( const vector< Card > newHand )
{
	if( newHand.size() != 2 )
		throw InvalidHandException( name );
	
	hand = newHand;
}

vector< Card > Player::getHand()
{
	return hand;
}

void Player::changeState( State newState )
{
	if( state == PLAYING )
		state = newState;
	else
		throw InvalidStateException( name );
}

void Player::setStatePlaying()
{
	state = PLAYING;
}

State Player::getState()
{
	return state;
}
