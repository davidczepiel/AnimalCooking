#pragma once
#include "Component.h"
#include "SwitcherKeyboard.h"

class KeyboardKeySwitcher : public Component
{
public:
	KeyboardKeySwitcher(int player, int buttonWidth, int buttonHeight) : Component(ecs::KeyboardKeySwitcher),
		switchers_(), player_(player), buttonWidth_(buttonWidth), buttonHeight_(buttonHeight) {}
	~KeyboardKeySwitcher() {
		for (SwitcherKeyboard* s : switchers_)
			delete s;
	}
	const vector<SwitcherKeyboard*>& getSwitchers() const { return switchers_; }
	const int& getPlayer() const { return player_; }

	void init();
	void update() override;

private:
	vector<SwitcherKeyboard*> switchers_;
	int player_;
	int buttonWidth_, buttonHeight_;
};

