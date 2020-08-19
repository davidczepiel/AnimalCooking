#pragma once
#include "Component.h"
#include "KeyboardKeySwitcher.h"
#include "Transform.h"

class KeyboardKeySwitcherViewer : public Component
{
public:
	KeyboardKeySwitcherViewer(Texture* clickTexture) : Component(ecs::KeyboardKeySwitcherViewer), t(nullptr), logic_(nullptr), clickTexture_(clickTexture){}
	void init() override;
	void draw() override;
private:
	Transform* t;
	KeyboardKeySwitcher* logic_;
	Texture* clickTexture_;
};


