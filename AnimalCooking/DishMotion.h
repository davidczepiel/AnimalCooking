#pragma once
#include "Component.h"
#include"DishPool.h"

class DishMotion : public Component
{
public:
	DishMotion();
	~DishMotion() { }

	void init()override;
	void update()override;

private:

	DishPool* dp = nullptr;
	
};