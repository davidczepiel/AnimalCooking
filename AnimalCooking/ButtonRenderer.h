#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"


class ButtonRenderer : public Component
{
public:
	ButtonRenderer(Texture* background, Texture* text);
	void init() override;
	void draw() override;
	void clicked() { clickedTime_ = game_->getTime(); }
	inline void setActive(bool val) { active = val; }
private:
	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;

	Texture* background_;
	Texture* text_;

	Uint32 clickedTime_, clickedTimeCD_;
	bool active;

	enum ButtonState : size_t {
		Focushed,
		Unfocushed,
		Cliked,
	};

};

