#pragma once
#include "Adversity.h"
#include "MultipleAdversityManager.h"
#include "Timer.h"

class BurnedCookerAdversity : public Adversity
{
public:
	BurnedCookerAdversity(MultipleAdversityManager* mam);
	~BurnedCookerAdversity() {}

	void update();
	void draw();
	void reset();

private:
	void StartAdversity();

	Timer* internalTimer_;
	CookerPool* cookerPool_;
	Cooker* targetCooker_;

	bool alreadyInitialized_;	
};

