// File: InvalidPlayersContainerException.h
// Declaration of class InvalidPlayersContainerException.

#ifndef INVALIDPLAYERSCONTAINEREXCEPTION_H
#define INVALIDPLAYERSCONTAINEREXCEPTION_H

#include <stdexcept>
#include <string>

using namespace std;

class InvalidPlayersContainerException : public logic_error
{
public:
	InvalidPlayersContainerException( ) : logic_error( "Exception: attempted to use a invalid players container (not cyclycally ordered)." ){}
};

#endif
