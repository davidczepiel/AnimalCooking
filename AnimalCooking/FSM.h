#pragma once
#include<stack>
#include"State.h"
using namespace std;
class FSM
{
private:
	stack<State*> statesStack;
	SDLGame* game;
public:
	FSM(SDLGame* game):game(game){}
	void PushState(State* s);
	void PopState();
	State* CurrentState();
};

