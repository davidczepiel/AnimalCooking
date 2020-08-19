#pragma once
#include "Component.h"
#include "GpadKeySwitcher.h"
#include "Transform.h"
class GpadKeySwitcherViewer : public Component
{
public:
	GpadKeySwitcherViewer(Texture* clickTexture) : Component(ecs::GpadKeySwitcherViewer), t(nullptr), logic_(nullptr), clickTexture_(clickTexture) {}
	void init() override;
	void draw() override;
private:
	Transform* t;
	GpadKeySwitcher* logic_;
	Texture* clickTexture_;
};
