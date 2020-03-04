#pragma once

#include "checkML.h"
#include"Entity.h"

using namespace std;

class AnimalCooking;

class State
{
protected:
	EntityManager* stage = nullptr;

public:
	State();
	virtual ~State() { delete stage; }
	virtual void update();
	virtual void draw();
	virtual void handleEvent() {};
	
};

