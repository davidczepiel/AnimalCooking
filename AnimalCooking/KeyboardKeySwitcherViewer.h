#pragma once
#include "Component.h"
#include "KeyboardKeySwitcher.h"
#include "Transform.h"

class KeyboardKeySwitcherViewer : public Component
{
public:
	KeyboardKeySwitcherViewer() : Component(ecs::KeyboardKeySwitcherViewer), t(nullptr), logic_(nullptr) {}
	void init() override;
	void draw() override;
private:
	Transform* t;
	KeyboardKeySwitcher* logic_;
};


