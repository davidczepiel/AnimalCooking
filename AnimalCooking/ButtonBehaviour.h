#pragma once
#include "Component.h"
#include "Transform.h"
class AnimalCooking;
class ButtonBehaviour : public Component
{
	using CallBackOnClick = void(AnimalCooking* ac);
private:
	bool active_;
	CallBackOnClick* callback_;
	Transform* ownerTransform_;
	AnimalCooking* ac_;

public:
	ButtonBehaviour(CallBackOnClick* callback,AnimalCooking* ac);
	void init() override;
	void update() override; //Aqui se hace la comprobacion con el tramsform de si se le hace click y se llama al callback
	
	inline bool isActive() { return active_;}
	inline void setActive(bool active) { active_ = active; }
};

