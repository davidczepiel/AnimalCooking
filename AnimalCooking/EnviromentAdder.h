#pragma once

#include "Manager.h"
#include "EnviromentPool.h"
#include "EnviromentViewer.h"

class EnviromentAdder
{
public:
	EnviromentAdder(jute::jValue& nivel, EntityManager* mngr, std::array<Entity*, 2>& players,
		 const double casillaX, const double casillaY);
};

