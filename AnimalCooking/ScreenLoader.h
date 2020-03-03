#pragma once
#include "State.h"
class ScreenLoader : public State
{
public:	
	ScreenLoader(Resources::Level nivel);
	void resetResources(Resources::Level nivel); // Resources::Nivel nivel: es un enum que indica que recursos cargar en memoria
private:
	Entity* barraCarga_;
	Entity* buttonGo_;
};

