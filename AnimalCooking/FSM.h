#pragma once
#include<stack>
#include "checkML.h"
#include"State.h"
using namespace std;
class FSM
{
private:
	stack<State*> statesStack;
	SDLGame* game;
public:
	FSM(SDLGame* game):game(game){}
	virtual ~FSM();
	void PushState(State* s);
	void PopState();
	State* CurrentState();
};

