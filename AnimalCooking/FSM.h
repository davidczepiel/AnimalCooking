#pragma once
#include <stack>
#include "checkML.h"
#include"State.h"
#include <queue>
#include <functional>
using namespace std;

class FSM
{
private:
	struct Event {
		bool push;
		State* s;
		std::function<void()> f = nullptr;
	};
	queue<Event> events;
	stack<State*> statesStack;
public:
	FSM() {}
	virtual ~FSM();

	void pushState(State* s);
	void pushState(State* s, std::function<void()> f);
	void popState();
	void popState(std::function<void()> f);
	State* currentState();
	void changeState(State* s);
	void changeState(State* s, std::function<void()> f);
	void refresh();
};