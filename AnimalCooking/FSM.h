#pragma once
#include <stack>
#include "checkML.h"
#include"State.h"
#include <queue>
#include <functional>
using namespace std;

class FSM
{
public:
	FSM() {}
	virtual ~FSM();
	void pushState(State* s);
	void pushState(State* s, std::function<void()> f);
	void popState();
	void popState(std::function<void()> f);
	void changeState(State* s);
	void changeState(State* s, std::function<void()> f);
	void refresh();

	State* currentState();
	inline const size_t getStackSize() const { return statesStack.size(); }

private:
	struct Event {
		bool push;
		State* s;
		std::function<void()> f = nullptr;
	};
	queue<Event> events;
	stack<State*> statesStack;
};