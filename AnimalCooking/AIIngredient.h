#pragma once
#include "Component.h"
#include "IngredientsPool.h"
#include "Vector2D.h"
#include "Transform.h"

class AIIngredient : public Component
{
public:
	AIIngredient(IngredientsPool* ip, Transform* t1, Transform* t2);
	~AIIngredient() {}

	void update() override;
	void updateIngredientState(Ingredient* i);
	Vector2D calculateNewVel(Ingredient* tr);
	void NotCorner(Vector2D p1toIngredient, Vector2D p2toIngredient,Ingredient* ing);
	void Corner(Ingredient* ing);
private:
	IngredientsPool* ip_;
	Transform* t1_;
	Transform* t2_;
	double rangeX;
	double rangeY;
};

