#pragma once
#include<stack>
#include "checkML.h"
#include"State.h"
using namespace std;

class FSM
{
private:
	stack<State*> statesStack;

public:
	FSM() {}
	virtual ~FSM();

	void pushState(State* s);
	void popState();
	State* currentState();
};

