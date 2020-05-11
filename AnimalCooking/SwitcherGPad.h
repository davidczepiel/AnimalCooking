#pragma once
#include "KeySwitcher.h"
class SwitcherGPad : public KeySwitcher
{
public:
	SwitcherGPad(const Vector2D& pos, const Vector2D& size, SDL_GameControllerButton& change) : KeySwitcher(pos, size),
		gPad_keyToChange(change){}

	virtual void update();
private:
	SDL_GameControllerButton& gPad_keyToChange;
};

