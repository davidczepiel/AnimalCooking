#pragma once
#include <array>
#include "Entity.h"
#include "jute.h"
#include <list>
#include "Timer.h"
class EntityManager;
class Utensil;
class UtensilsPool;
class Shelf;
class Interactive;
class ShelfAdder
{
public:
	ShelfAdder(EntityManager* emPlayState, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, 
		UtensilsPool* pool_, const double casillaX, const double casillaY);
	std::vector<Interactive*>& getInteractives() { return interactives_; }
	std::list<Timer*>& getTimers() { return timers_; }
private:

	EntityManager* emPlayState;
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	std::vector<Interactive*> interactives_;
	const double casillaX;
	const double casillaY;

	Utensil* switchUten(const string& ing, UtensilsPool* pool_, std::array<Entity*, 2>& player);

	template<typename T>
	Utensil* makeUtensil(std::array<Entity*, 2>& player, UtensilsPool* pool_);

	Shelf* makeShelf(Utensil* u, std::array<Entity*, 2>& player, jute::jValue& jsonShelf);
	void initializeComponent(const string& component, Entity* entity);
	std::list<Timer*> timers_;

};
