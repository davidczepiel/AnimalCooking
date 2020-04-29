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

void FSM::pushState(State* s, std::function<void()> f)
{
	events.push({ true, s, f });
}

void FSM::popState()
{
	if (!statesStack.empty())
	{
		events.push({ false, nullptr });
	}
}

State* FSM::currentState() {
	return statesStack.top();
}

void FSM::changeState(State* s)
{
	popState();
	pushState(s);
}

void FSM::changeState(State* s, std::function<void()> f)
{
	popState();
	pushState(s, f);
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
		if (events.front().f != nullptr) {
			events.front().f();
		}
		events.pop();
	}
}

void FSM::popState(std::function<void()> f)
{
	if (!statesStack.empty()) 
	{ 
		events.push({ false, nullptr, f });
	}
}
