#pragma once

#include "checkML.h"
#include"Entity.h"

using namespace std;

class AnimalCooking;

class State
{

public:
	State(AnimalCooking* ac);
	State(EntityManager* em,AnimalCooking* ac);
	virtual ~State() { delete stage; }
	virtual void update();
	virtual void draw();
	virtual void handleEvent() {};

	inline AnimalCooking* getAnimalCooking() { return app; }

protected:
	EntityManager* stage = nullptr;
	AnimalCooking* app;	
};

