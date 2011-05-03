// File: InvalidPositionException.h
// Declaration of class InvalidPositionException.

#ifndef INVALIDPOSITIONEXCEPTION_H
#define INVALIDPOSITIONEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidPositionException : public logic_error
{
public:
	InvalidPositionException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to set a invalid position" ){}
};

#endif
