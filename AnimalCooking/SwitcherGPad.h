#pragma once
#include "KeySwitcher.h"
class SwitcherGPad : public KeySwitcher
{
public:
	SwitcherGPad(const Vector2D& pos, const Vector2D& size, SDL_GameControllerButton& change, const string& name) : KeySwitcher(pos, size, name),
		gPad_keyToChange(change){}

	virtual void update();
	virtual void draw();
private:
	SDL_GameControllerButton& gPad_keyToChange;
};

