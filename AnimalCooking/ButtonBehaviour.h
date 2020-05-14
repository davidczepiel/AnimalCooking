#pragma once
#include "Component.h"
#include "Transform.h"
class ButtonRenderer;
class AnimalCooking;
class ButtonBehaviour : public Component
{
	using CallBackOnClick = void(AnimalCooking* ac);
private:
	bool active_;
	bool focusedByMouse_, focusedByController_;
	CallBackOnClick* callback_;
	Transform* ownerTransform_;
	AnimalCooking* ac_;
	ButtonRenderer* bRenderer_;
public:
	ButtonBehaviour(CallBackOnClick* callback,AnimalCooking* ac);

	void setButtonRenderer(ButtonRenderer* bR) { bRenderer_ = bR; }

	void init() override;
	void update() override; //Aqui se hace la comprobacion con el tramsform de si se le hace click y se llama al callback
	const bool& getFocusByMouse() { return focusedByMouse_; }
	const bool& getFocusByController() { return focusedByController_; }
	void setFocusByController(bool f) { focusedByController_ = f; }
	void action();
	inline bool isActive() { return active_;}
	inline void setActive(bool active) { active_ = active; }
};

