// File: InvalidStateException.h
// Declaration of class InvalidStateException.

#ifndef INVALIDSTATEEXCEPTION_H
#define INVALIDSTATEEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidStateException : public logic_error
{
public:
	InvalidStateException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to set a invalid state" ){}
};

#endif
