#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "FoodCooker.h"
#include "Food.h"
#include "Transport.h"

class InsertExpel: public Component {
public:
	InsertExpel(Transport *tr1, Transport* tr2);
	~InsertExpel();
	void init() override;
	void insertFood(Cooker* c, int player);
	void extractFood(Cooker *c, Timer* timer, int player);

private:
	FoodCooker* foodCooker_;
	Transport* transport1_, *transport2_;
};