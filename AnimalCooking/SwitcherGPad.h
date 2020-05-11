#pragma once
#include "KeySwitcher.h"
#include "Transform.h"
class SwitcherGPad : public KeySwitcher
{
public:
	SwitcherGPad(const Vector2D& pos, const Vector2D& size, SDL_GameControllerButton& change, const string& name, int player) : KeySwitcher(pos, size, name),
		player_(player), gPad_keyToChange(change){}

	virtual void update();
	virtual void draw();
private:
	int player_;
	SDL_GameControllerButton& gPad_keyToChange;
};

