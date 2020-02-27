#pragma once
#include "State.h"
class LoadState : public State
{
public:

	//LoadState(/*Resources::Nivel nivel*/); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
//	void resetResources(Resources::Nivel nivel); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
//private:
//	Entity* barraCarga_;
//	Entity* buttonGo_;
	LoadState() :State() { cout << "load"; }
};

