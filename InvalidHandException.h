// File: InvalidHandException.h
// Declaration of class InvalidHandException.

#ifndef INVALIDHANDEXCEPTION_H
#define INVALIDHANDEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidHandException : public logic_error
{
public:
	InvalidHandException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to set a invalid hand" ){}
};

#endif
