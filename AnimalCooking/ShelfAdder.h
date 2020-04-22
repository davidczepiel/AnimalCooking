#pragma once
#include <array>
#include "Entity.h"
#include "jute.h"

class EntityManager;
class Utensil;
class UtensilsPool;
class Shelf;
class Interactive;
class ShelfAdder
{
public:
	ShelfAdder(EntityManager* emPlayState, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, UtensilsPool* pool_, const double casilla, const double offset);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
private:

	EntityManager* emPlayState;
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	std::vector<Interactive*> interactives_;
	const double casillaLength, offset;

	Utensil* switchUten(const string& ing, UtensilsPool* pool_, std::array<Entity*, 2>& player);

	template<typename T>
	Utensil* makeUtensil(std::array<Entity*, 2>& player, UtensilsPool* pool_);

	Shelf* makeShelf(Utensil* u, std::array<Entity*, 2>& player, jute::jValue& jsonShelf);
	void initializeComponent(const string& component, Entity* entity);
	
};
