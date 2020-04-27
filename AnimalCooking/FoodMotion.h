#pragma once
#include "FoodPool.h"
#include "Component.h"

class FoodMotion : public Component
{
private:
	FoodPool* foodPool_;
public:
	FoodMotion();
	void update() override;
	void init() override;
};
