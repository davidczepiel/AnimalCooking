#pragma once
#include "Component.h"
#include "Transform.h"
class ButtonRenderer;
class ButtonCheckRenderer;
class AnimalCooking;
class ButtonBehaviour : public Component
{
	using CallBackOnClick = void(AnimalCooking* ac);

public:
	ButtonBehaviour(CallBackOnClick* callback,AnimalCooking* ac);
	void init() override;
	void update() override; //Aqui se hace la comprobacion con el tramsform de si se le hace click y se llama al callback
	void action();

	void setButtonRenderer(ButtonRenderer* bR) { bRenderer_ = bR; }	
	void setButtonCheckRenderer(ButtonCheckRenderer* bcr) { bcRenderer_ = bcr; }
	const bool& getFocusByMouse() { return focusedByMouse_; }
	const bool& getFocusByController() { return focusedByController_; }
	void setFocusByController(bool f) { focusedByController_ = f; }	
	inline bool isActive() { return active_;}
	inline void setActive(bool active) { active_ = active; }

private:
	bool active_;
	bool focusedByMouse_, focusedByController_;
	CallBackOnClick* callback_;
	Transform* ownerTransform_;
	AnimalCooking* ac_;
	ButtonRenderer* bRenderer_;
	ButtonCheckRenderer* bcRenderer_;
};

