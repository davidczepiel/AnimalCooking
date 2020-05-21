#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"

class ButtonChangeOnClick;
class ButtonRenderer : public Component
{
public:
	ButtonRenderer(Texture* background, Texture* text);
	void init() override;
	void draw() override;
	void clicked();
	inline void setActive(bool val) { active = val; }
private:
	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;
	ButtonChangeOnClick* buttonOnClick_;
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

