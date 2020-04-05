#pragma once
#include <array>
#include "Entity.h"
#include "jute.h"

class EntityManager;
class Utensil;
class UtensilsPool;
class Shelf;
class ShelfAdder
{
public:
	ShelfAdder(EntityManager* emPlayState, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, UtensilsPool* pool_, const double casilla);
private:

	EntityManager* emPlayState;
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	const double casillaLength;

	Utensil* switchUten(const string& ing, UtensilsPool* pool_, std::array<Entity*, 2>& player);

	template<typename T>
	Utensil* makeUtensil(std::array<Entity*, 2>& player, UtensilsPool* pool_);

	Shelf* makeShelf(Utensil* u, std::array<Entity*, 2>& player, jute::jValue& jsonShelf);
	void initializeComponent(const string& component, Entity* entity);
};
