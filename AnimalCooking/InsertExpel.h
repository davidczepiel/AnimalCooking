#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "FoodCooker.h"
#include "Food.h"
//#include "Transport.h"

class InsertExpel: public Component {
public:
	InsertExpel();
	//InsertExpel(Transport *tr);
	~InsertExpel();
	void init() override;

	//void insertFood(Cooker *c, list<Food*>& f);
	void insertFood(Cooker* c);

	void extractFood(Cooker *c, int foodSelectorPosition);
	void extractAllFood(Cooker *c);

private:
	FoodCooker* foodCooker_;
	//Transport* transport_;
};