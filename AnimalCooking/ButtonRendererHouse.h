#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"

class ButtonBehaviourNC;
class ButtonRendererHouse : public Component
{
public:
	ButtonRendererHouse(Texture* background, Texture* text, levelInfo* info);

	void init() override;
	void draw() override;
	void clicked() { clickedTime_ = game_->getTime(); }

	inline void setActive(bool val) { active = val; }
	inline void setLevel(levelInfo* l) { info = l; }


private:
	enum ButtonState : size_t {
		Unfocushed,
		Focushed,
		Locked,
	};

	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;
	ButtonBehaviourNC* buttonBehaviourNC_;
	levelInfo* info;
	Texture* background_;
	Texture* text_;

	Uint32 clickedTime_, clickedTimeCD_;
	bool active;	
};

