#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include"MapState.h"
#include "FSM.h"
class NameAsker :
	public Component
{
public:
	NameAsker() : Component(ecs::nameAsker), bg(nullptr), casillaX(0),casillaY(0),name(" "),nameStream(name) {
		ih = SDLGame::instance()->getInputHandler();
	}
	//virtual ~NameAsker(){ static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState())->setPlayerName(name); }
	virtual void draw()override;
	virtual void init()override;
	virtual void update()override;
private:
	Texture* bg;
	string name;
	stringstream nameStream;
	double casillaX;
	double casillaY;
	InputHandler* ih;
	
};

