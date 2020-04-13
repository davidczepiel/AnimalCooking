#pragma once
#include "Adversity.h"
#include "AdversityManager.h"
#include "Timer.h"

class BurnedCookerAdversity : public Adversity
{
	Timer internalTimer;
	CookerPool* cookerPool;
	Cooker* targetCooker;

	void StartAdversity();

public:
	BurnedCookerAdversity(AdversityManager* am) : Adversity(am), cookerPool(am->getCookerPool) { StartAdversity(); }
	~BurnedCookerAdversity() {}

	void update();
	void draw();
	void reset();
};

