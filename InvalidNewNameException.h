// File: InvalidNewNameException.h
// Declaration of class InvalidNewNameException.

#ifndef INVALIDNEWNAMEEXCEPTION_H
#define INVALIDNEWNAMEEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class InvalidNewNameException : public logic_error
{
public:
	InvalidNewNameException( ) : logic_error( "Exception: attempted create a player using invalid name" ){}
};

#endif
