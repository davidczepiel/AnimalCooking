#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"

class ButtonBehaviourNC;
class ButtonRendererHouse : public Component
{
public:
	ButtonRendererHouse(Texture* background, Texture* text, int level);
	void init() override;
	void draw() override;
	void clicked() { clickedTime_ = game_->getTime(); }
	inline void setActive(bool val) { active = val; }
	inline void setLevel(int l) { level = l; }
private:
	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;
	ButtonBehaviourNC* buttonBehaviourNC_;

	Texture* background_;
	Texture* text_;

	Uint32 clickedTime_, clickedTimeCD_;
	bool active;
	int level;

	enum ButtonState : size_t {
		Unfocushed,
		Focushed,	
		Locked,
	};
};

