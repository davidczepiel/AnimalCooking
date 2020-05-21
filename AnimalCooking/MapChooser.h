#pragma once
#include "Component.h"
#include "Entity.h"
#include "SDL_macros.h"
#include"MapState.h"
#include "FSM.h"

class MapChooser :public Component {
public:
	MapChooser();
	virtual void draw()override;
	virtual void init()override;

	inline void setActive(bool a) { active_ = a; }
private:
	Texture* bgText_;
	Texture* buttonTexture_;
	double casillaX_;
	double casillaY_;
	bool active_;
};

