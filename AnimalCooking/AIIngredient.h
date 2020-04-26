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
	Uint32 timeWalking;
	Uint32 timeIdle;
	double range;
public:
	AIIngredient(IngredientsPool* ip, Transform* t1, Transform* t2) : Component(ecs::AIIngredient), ip_(ip), t1_(t1), t2_(t2), timeWalking(800), timeIdle(500), range(250) {}
	~AIIngredient() {}

	void update() override;
	void updateIngredientState(Ingredient* i);
	Vector2D calculateNewVel(Ingredient* tr);
};

