#pragma once
#include "Adversity.h"
#include "AdversityManager.h"
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
	BurnedCookerAdversity(AdversityManager* am, MultipleAdversityManager* mam) : Adversity(am, mam), 
		cookerPool(mam->getCookerPool()), internalTimer(new Timer()), alreadyInitialized(false) { }
	~BurnedCookerAdversity() {}

	void update();
	void draw();
	void reset();
};

