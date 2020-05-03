#pragma once
#include "Component.h"
#include "Transform.h"

class MenuState;

using CallBackOnClick = void();

class MenuButtonBehaviour : public Component
{
public:
	enum ButtonType { RightArr, LeftArrow, SelectionButton};
	MenuButtonBehaviour(MenuState* ms, ButtonType t) : Component(ecs::MenuButtonBehaviour), ms_(ms),buttonType_(t) {}
	~MenuButtonBehaviour() { tr_ = nullptr; }

	void init() override;
	void update() override;
	void action();
	ButtonType getButtonType() { return buttonType_; }
private:
	Transform* tr_;
	MenuState* ms_;
	ButtonType buttonType_;
};

