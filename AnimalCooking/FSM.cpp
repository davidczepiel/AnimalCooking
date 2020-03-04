#include "FSM.h"
#include"checkML.h"

FSM::~FSM()
{
	while (!statesStack.empty())
	{
		delete statesStack.top();
		statesStack.pop();
	}
}

void FSM::pushState(State* s) {
	statesStack.push(s);
}

State* FSM::currentState() {
	return statesStack.top();
}

void FSM::popState()
{
	if (!statesStack.empty()) 
	{ 
		delete statesStack.top();
		statesStack.pop(); 
	}
}
