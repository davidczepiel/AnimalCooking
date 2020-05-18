#pragma once
#include "KeySwitcher.h"
#include "Transform.h"
class SwitcherGPad : public KeySwitcher
{
public:
	SwitcherGPad(const Vector2D& pos, const Vector2D& size, SDL_GameControllerButton& change, const Resources::TextureId& name, int player) : KeySwitcher(pos, size, name),
		player_(player), focused_(false), gPad_keyToChange(change){}

	virtual void update();
	virtual void draw();
private:
	int player_;
	bool focused_;
	SDL_GameControllerButton& gPad_keyToChange;
};

