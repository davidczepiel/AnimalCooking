#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"

class ButtonBehaviourNC;
class ButtonChangeOnClick;
class ButtonCheckRenderer : public Component
{
public:
	ButtonCheckRenderer(Texture* textFocused, Texture* textUnFocused);
	void init() override;
	void draw() override;

	void clicked();

	inline void setActive(bool val) { active = val; }

	void setCheckedAndUncheckedTextures(Resources::TextureId checked, Resources::TextureId unChecked) {
		checked_ = game_->getTextureMngr()->getTexture(checked);
		unChecked_ = game_->getTextureMngr()->getTexture(unChecked);
	}

private:
	enum ButtonState : size_t {
		Focushed,
		Unfocushed,
	};

	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;
	ButtonBehaviourNC* buttonBehaviourNC_;
	ButtonChangeOnClick* buttonOnClick_;

	Texture* checked_;
	Texture* unChecked_;
	Texture* textFocused_;
	Texture* textUnFocused_;

	bool active;
};

