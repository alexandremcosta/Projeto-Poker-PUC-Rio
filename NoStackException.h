// File: NoStackException.h
// Declaration of class NoStackException.

#ifndef NOSTACKEXCEPTION_H
#define NOSTACKEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class NoStackException : public logic_error
{
public:
	NoStackException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to bet without stack" ){}
};

#endif
