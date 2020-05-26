#pragma once
#include "FoodPool.h"
#include "Component.h"

class FoodMotion : public Component
{
public:
	FoodMotion();
	void update() override;
	void init() override;

private:
	FoodPool* foodPool_;
};
