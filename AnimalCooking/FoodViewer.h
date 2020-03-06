#pragma once
#include "FoodPool.h"
#include "Component.h"
#include "FoodPool.h"
class FoodViewer : public Component
{
private:
	FoodPool* foodPool_;
public:
	void draw() override;
	void init() override;
};

