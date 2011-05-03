// File: Player.h
// Declaration of class Player.

#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include "DeckOfCards.h"

using namespace std;

typedef enum {
         PLAYING,
         ALLIN,
         FOLDED,
         OUT
} State ;
   
typedef enum {
         DEALER,
         SMALLBLIND,
         BIGBLIND,
} Position ;

// Player class definition
class Player
{
public:
	Player( string newName );
	
	string getName();
	
	int calculateBet( int, int, int );
	int calculateBet( vector< Card >, int );
	
	void setStack( int );
	int getStack();
	void increaseStack( int );
	void decreaseStack( int );
	
	void setPosition( int );
	int getPosition();

	void setHand( const vector< Card > );
	vector< Card > getHand();
	
	void changeState( State ); // Only allows changes from PLAYING to another state
	void setStatePlaying();
	State getState();
	
private:
	string name;
	int stack;
	int position; // 0 - Dealer, 1 - Small Blind ...
	vector< Card > hand;
	State state;
};

#endif
