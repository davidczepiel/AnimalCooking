#pragma once
#include "Component.h"
#include "CookerPool.h"

class FoodCooker : public Component {
public:
	FoodCooker();
	~FoodCooker();
	void init() override;
	void update() override;
	void startCooked(Cooker *c);
	
private:
	vector <Cooker*> pool_;
};