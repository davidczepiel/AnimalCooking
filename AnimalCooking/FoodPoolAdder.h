#pragma once
#include "jute.h"
#include <string>
#include "Entity.h"

class FoodPoolAdder
{
public:
	FoodPoolAdder(Entity* foodPool, jute::jValue jsonLevel, jute::jValue jsonGeneral, std::array<Entity*, 2>& players);
private:
	Entity* foodPool;
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	void initializeComponent(const string& component, Entity* entity);
};

