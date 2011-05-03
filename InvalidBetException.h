// File: InvalidBetException.h
// Declaration of class InvalidBetException.

#ifndef INVALIDBETEXCEPTION_H
#define INVALIDBETEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidBetException : public logic_error
{
public:
	InvalidBetException( string playerName ) : logic_error( "Exception: Player " + playerName + " attempted to bet a invalid amount" ){}
};

#endif
