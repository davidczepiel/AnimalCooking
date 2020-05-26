#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "FoodPool.h"

class FoodCooker : public Component {
public:
	FoodCooker(FoodPool* fp);
	~FoodCooker();

	void init() override;
	void update() override;

	void startCooked(Cooker *c);
	void clearFoods(Cooker *c);
private:
	CookerPool* pool_;
	FoodPool* fp_;
};