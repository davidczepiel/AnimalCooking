#pragma once

#include "checkML.h"
#include"Entity.h"

using namespace std;

class AnimalCooking;

class State
{
protected:
	EntityManager* stage = nullptr;
	AnimalCooking* app_ = nullptr;

public:
	State(AnimalCooking* app);
	virtual ~State() { delete stage; }
	void update();
	void draw();
	
};

