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

void FSM::PushState(State* s) {
	statesStack.push(s);
}

State* FSM::CurrentState() {
	return statesStack.top();
}

void FSM::PopState()
{
	if (!statesStack.empty()) 
	{ 
		delete statesStack.top();
		statesStack.pop(); 
	}
}
