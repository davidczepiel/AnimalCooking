#pragma once
#include "Component.h"

#include "SwitcherGPad.h"

class GpadKeySwitcher : public Component
{
public:
	GpadKeySwitcher(int player, int buttonWidth, int buttonHeight) : Component(ecs::GpadKeySwitcher), 
		switchers_(), player_(player), buttonWidth_(buttonWidth), buttonHeight_(buttonHeight) {}
	~GpadKeySwitcher() {
		for (SwitcherGPad* s : switchers_)
			delete s;
	}
	void init();
	void update() override;

	const vector<SwitcherGPad*>& getSwitchers() const { return switchers_; }
	const int& getPlayer() const { return player_; }

private:
	vector<SwitcherGPad*> switchers_;
	int player_;
	int buttonWidth_, buttonHeight_;
};
