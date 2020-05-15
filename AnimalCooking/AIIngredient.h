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
	double rangeX;
	double rangeY;
public:
	AIIngredient(IngredientsPool* ip, Transform* t1, Transform* t2);
	~AIIngredient() {}

	void update() override;
	void updateIngredientState(Ingredient* i);
	Vector2D calculateNewVel(Ingredient* tr);
};

