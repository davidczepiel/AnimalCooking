#pragma once
#include "Component.h"
class GpadKeySwitcher : public Component
{
public:
	GpadKeySwitcher(int player) : Component(ecs::GpadKeySwitcher), player_(player) {}

private:
	int player_;
};



