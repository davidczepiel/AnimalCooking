#pragma once
#include "State.h"
class ScreenLoader : public State
{
public:	
	ScreenLoader(Resources::Nivel nivel);
	void resetResources(Resources::Nivel nivel); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
private:
	Entity* barraCarga_;
	Entity* buttonGo_;
};

