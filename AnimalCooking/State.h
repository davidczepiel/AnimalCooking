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
	virtual ~State() {}
	void Update();
	void Draw();
	
};

