#pragma once
#include<stack>
#include"State.h"
using namespace std;
class FSM
{
private:
	stack<State*> statesStack;
public:
	void PushState(State* s);
	void PopState();
	State* CurrentState();
};

