// File: EmptyDeckException.h
// Declaration of class EmptyDeckException.

#ifndef EMPTYDECKEXCEPTION_H
#define EMPTYDECKEXCEPTION_H

#include <stdexcept>
using namespace std;

class EmptyDeckException : public logic_error
{
public:
	EmptyDeckException() : logic_error( "attempted to deal a card from an empty deck" ){}
};

#endif
