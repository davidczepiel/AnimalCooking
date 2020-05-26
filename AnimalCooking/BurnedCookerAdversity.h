#pragma once
#include "Adversity.h"
#include "MultipleAdversityManager.h"
#include "Timer.h"

class BurnedCookerAdversity : public Adversity
{
	Timer* internalTimer;
	CookerPool* cookerPool;
	Cooker* targetCooker;
	bool alreadyInitialized;

	void StartAdversity();

public:
	BurnedCookerAdversity(MultipleAdversityManager* mam) : Adversity(mam), 
		cookerPool(mam->getCookerPool()), internalTimer(new Timer()), alreadyInitialized(false) { }
	~BurnedCookerAdversity() {}

	void update();
	void draw();
	void reset();
};

