#pragma once
#include "KeySwitcher.h"
#include "Transform.h"
class SwitcherGPad : public KeySwitcher
{
public:
	SwitcherGPad(const Vector2D& pos, const Vector2D& size, SDL_GameControllerButton& change, const Resources::TextureId& name, int player) : KeySwitcher(pos, size, name),
		alpha_(255), startedTime_(), player_(player), focused_(false), gPad_keyToChange(change) {}

	virtual void update();
	virtual void draw();
private:
	SDL_GameControllerButton& gPad_keyToChange;
	Uint8 alpha_;
	Uint32 startedTime_;
	int player_;
	bool focused_;
};

class SwitcherGPad_Boolean : public KeySwitcher
{
public:
	SwitcherGPad_Boolean(const Vector2D& pos, const Vector2D& size, bool& change, const Resources::TextureId& name, int player) : KeySwitcher(pos, size, name),
		player_(player), focused_(false), gPad_boolToChange(change)
	{
		if (change) state = State::ps4;
		else state = State::xbox;
	}

	virtual void update();
	virtual void draw();
private:
	enum State : int {
		xbox,
		xboxChanging,
		ps4,
		ps4Changing
	};
	State state;
	bool& gPad_boolToChange;
	int player_;
	bool focused_;
};