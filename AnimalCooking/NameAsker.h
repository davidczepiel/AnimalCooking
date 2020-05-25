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
	inline bool getActive() { return active; }
	inline string getName() { return nameStream.str(); }
private:
	Texture* bg;
	stringstream nameStream;
	double casillaX;
	double casillaY;
	double nameWidth_;
	InputHandler* ih;
	bool active;	
};

