#pragma once
#include "Component.h"

#include "SwitcherGPad.h"

class GpadKeySwitcher : public Component
{
public:
	GpadKeySwitcher(int player, int buttonWidth, int buttonHeight, bool navEnabled) : Component(ecs::GpadKeySwitcher),
		focus(1), switchers_(), player_(player), buttonWidth_(buttonWidth), buttonHeight_(buttonHeight), navEnabled(navEnabled), update_(true) {}
	~GpadKeySwitcher() {
		for (KeySwitcher* s : switchers_)
			delete s;
	}
	const vector<KeySwitcher*>& getSwitchers() const { return switchers_; }
	const int& getPlayer() const { return player_; }
	inline const bool& onTop() { return focus == 0; }

	void setFocushed(const int& delta);

	void init();
	void update() override;
	//Adds delta to focus and then it modules by 6
	void addFocushed(const int& delta);

private:
	vector<KeySwitcher*> switchers_;
	bool navEnabled, update_;
	int focus;
	int player_;
	int buttonWidth_, buttonHeight_;
};
