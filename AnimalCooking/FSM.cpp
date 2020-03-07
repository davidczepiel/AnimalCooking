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
	events.push({ true, s });
}

State* FSM::currentState() {
	return statesStack.top();
}

void FSM::changeState(State* s)
{
	popState();
	pushState(s);
}

void FSM::refresh()
{
	while (!events.empty()) {
		if (events.front().push) {
			statesStack.push(events.front().s);
		}
		else {
			delete statesStack.top();
			statesStack.pop();
		}
		events.pop();
	}
}

void FSM::popState()
{
	if (!statesStack.empty()) 
	{ 
		events.push({ false, nullptr });
	}
}
