#pragma once
#include "Entity.h"
#include "jute.h"

class PlayersAdder
{
public:
	PlayersAdder(std::array<Entity*, 2>& players, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, const double casillaX, const double casillaY, EntityManager* em);
private:

	std::array<Entity*, 2> players{};
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	void players_addComponents(Entity* entity, int id);
	void players_initializeTransform(size_t player, const double casillaX, const double casillaY);

	void initializeComponent(const string& component, Entity* entity);

	double casillaX;
	double casillaY;
};
