#pragma once
#include "Component.h"
#include "AnimalCooking.h"
#include "Transform.h"
class ButtonBehaviour : public Component
{
	using CallBackOnClick = void(AnimalCooking* animalcooking);
private:
	CallBackOnClick* callback_;
	Transform* ownerTransform_;

public:
	ButtonBehaviour(CallBackOnClick* callback);
	void init() override;
	void update() override; //Aqui se hace la comprobacion con el tramsform de si se le hace click y se llama al callback
};

