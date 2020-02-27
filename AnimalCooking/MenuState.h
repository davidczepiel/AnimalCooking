#pragma once
#include "State.h"
class MenuState: public State
{
public:
	MenuState() :State() { cout << "menu"; }
};

