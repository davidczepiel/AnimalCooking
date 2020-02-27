#pragma once
#include "State.h"
class LoadState :
	public State
{
public:
	LoadState() :State() { cout << "load"; }
};

