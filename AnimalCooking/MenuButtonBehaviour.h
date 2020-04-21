#pragma once
#include "Component.h"
#include "Transform.h"

class MenuState;

class MenuButtonBehaviour : public Component
{
private:
	Transform* tr_;
	MenuState* menuState_;
	bool right_;
public:
	MenuButtonBehaviour(MenuState* ms, bool isRight) : Component(ecs::MenuButtonRenderer), menuState_(ms), right_(isRight) {}
	~MenuButtonBehaviour() { menuState_ = nullptr; tr_ = nullptr; }

	void init() override;
	void update() override;
};

