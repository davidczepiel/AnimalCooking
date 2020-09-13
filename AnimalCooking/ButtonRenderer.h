#pragma once
#include "Component.h"
#include "Transform.h"
#include "ButtonBehaviour.h"

class ButtonBehaviourNC;
class ButtonChangeOnClick;
class ButtonRenderer : public Component
{
public:
	ButtonRenderer(Texture* background, Texture* text);
	void init() override;
	void draw() override;
	
	void clicked();
	inline void setActive(bool val) { active = val; }

protected:
	enum ButtonState : size_t {
		Focushed,
		Unfocushed,
		Cliked,
	};

	Transform* ownerTransform_;
	ButtonBehaviour* buttonBehaviour_;
	ButtonBehaviourNC* buttonBehaviourNC_;
	ButtonChangeOnClick* buttonOnClick_;	
	Texture* background_;
	Texture* text_;

	Uint32 clickedTime_, clickedTimeCD_;
	bool active;
};

class ButtonRendererMapArrow : public ButtonRenderer
{
public: 
	ButtonRendererMapArrow(Texture* background, Texture* text) : ButtonRenderer(background, text), available(true) {}
	~ButtonRendererMapArrow() {}

	void init() override;
	void draw() override;

	inline void setAvailable(bool av_) { available = av_; }
private:
	bool available;
};

