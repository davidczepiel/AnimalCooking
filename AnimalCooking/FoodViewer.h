#pragma once
#include "FoodPool.h"
#include "Component.h"
#include "FoodPool.h"
#include "Entity.h"
class FoodViewer : public Component
{
private:
	FoodPool* foodPool_;
public:
	FoodViewer();
	void draw() override;
	void init() override;
};

