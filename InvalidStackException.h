// File: InvalidStackException.h
// Declaration of class InvalidStackException.

#ifndef INVALIDSTACKEXCEPTION_H
#define INVALIDSTACKEXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidStackException : public logic_error
{
public:
	InvalidStackException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to set a invalid stack value" ){}
};

#endif
