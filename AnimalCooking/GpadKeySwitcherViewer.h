#pragma once
#include "Component.h"
#include "GpadKeySwitcher.h"
#include "Transform.h"
class GpadKeySwitcherViewer : public Component
{
public:
	GpadKeySwitcherViewer() : Component(ecs::GpadKeySwitcherViewer), t(nullptr), logic_(nullptr) {}
	void init() override;
	void draw() override;

private:
	Transform* t;
	GpadKeySwitcher* logic_;
};
