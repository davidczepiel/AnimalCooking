#pragma once

#include "checkML.h"
#include"Entity.h"
using namespace std;

class State
{
protected:
	EntityManager* stage = nullptr;

public:
	State();
	virtual ~State() { delete stage; }
	void update();
	void draw();
	
};

