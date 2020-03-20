#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "FoodCooker.h"
#include "Food.h"
#include "Transport.h"

class InsertExpel: public Component {
public:
	InsertExpel(Transport *tr);
	~InsertExpel();
	void init() override;

	void insertFood(Cooker* c);
	void extractFood(Cooker *c);

private:
	FoodCooker* foodCooker_;
	Transport* transport_;
};