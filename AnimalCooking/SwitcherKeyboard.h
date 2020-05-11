#pragma once
#include "KeySwitcher.h"

class SwitcherKeyboard : public KeySwitcher
{
public: 
	SwitcherKeyboard(const Vector2D& pos, const Vector2D& size, SDL_Keycode& change, const string& name) : KeySwitcher(pos, size, name),
		keyToChange_(change) {}

	virtual void update();
	virtual void draw();
private:
	SDL_Keycode& keyToChange_;
};

