#pragma once
#include "Entity.h"
#include "jute.h"

class PlayersAdder
{
public:
	PlayersAdder(std::array<Entity*, 2>& players, jute::jValue& jsonLevel, jute::jValue& jsonGeneral);
private:

	std::array<Entity*, 2> players{};
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	void players_addComponents(Entity* entity);
	void players_initializeTransform(size_t player);
	void players_initializeExtraComponents();

	void initializeComponent(const string& component, Entity* entity);
};

