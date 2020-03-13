#pragma once
#include "Component.h"
#include "CookerPool.h"
#include "Food.h"
//#include "Transport.h"

class InsertExpel: public Component {
public:
	InsertExpel();
	//InsertExpel(Transport *tr);
	~InsertExpel();
	void init() override;

	void insertFood(Cooker *c, Food *f);
	void insertFood(Cooker* c);

	void extractFood(Cooker *c, int foodSelectorPosition);
	void extractAllFood(Cooker *c);

private:
	//Transport* transport_;
};