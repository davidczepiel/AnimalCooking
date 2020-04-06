#pragma once
#include "Component.h"

class Animator : public Component	
{
	
public:

	enum State {Idle, Walk, Attack};
	
	Animator();
	~Animator() { }

	State getCurrentState() { return currentState; };
	void setCurrentState(State s) { currentState = s; };
	SDL_Rect& animate(Texture* t, int fx, int fy,int numRows, int numCols);
private:

	State currentState;
	SDL_Rect clip;

};

