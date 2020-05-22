#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include"MapState.h"
#include "FSM.h"
class NameAsker :public Component{
public:
	NameAsker();
	virtual void draw()override;
	virtual void init()override;
	virtual void update()override;

	void setActive(bool a);
private:
	Texture* bg;
	stringstream nameStream;
	double casillaX;
	double casillaY;
	InputHandler* ih;
	bool active;	
};

