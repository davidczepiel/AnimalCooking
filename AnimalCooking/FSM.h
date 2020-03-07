#pragma once
#include <stack>
#include "checkML.h"
#include"State.h"
#include <queue>
using namespace std;

class FSM
{
private:
	struct Event {
		bool push;
		State* s;
	};
	queue<Event> events;
	stack<State*> statesStack;
public:
	FSM() {}
	virtual ~FSM();

	void pushState(State* s);
	void popState();
	State* currentState();
	void changeState(State* s);
	void refresh();
};

