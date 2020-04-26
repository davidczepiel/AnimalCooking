#pragma once
#include "Component.h"
#include "IngredientsPool.h"
#include "Transform.h"

class AIIngredient : public Component
{
private:
	IngredientsPool* ip_;
	Transform* t1_;
	Transform* t2_;
	Uint32 maxTimeWalking;
	Uint32 maxTimeIdle;
	double range;
public:
	AIIngredient(IngredientsPool* ip, Transform* t1, Transform* t2) : Component(ecs::AIIngredient), ip_(ip), t1_(t1), t2_(t2), maxTimeWalking(1000), maxTimeIdle(1000), range(250) {}
	~AIIngredient() {}

	void update() override;
	void updateIngredientState(Ingredient* i);
	Vector2D calculateNewVel(Ingredient* tr);
};

