#include "ShelfAdder.h"
#include "Shelf.h"
#include "SelectorPopUpEntity.h"
#include "Utensil.h"
#include "UtensilsPool.h"

#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)
#define ADD(t) makeUtensil<t>(player, pool_)
#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

ShelfAdder::ShelfAdder(EntityManager* emPlayState, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, UtensilsPool* pool_):
	emPlayState(emPlayState), jsonGeneral(jsonGeneral)
{
	jute::jValue shelfs_ = jsonLevel["Shelfs"]["entities"];
	jute::jValue components = jsonLevel["Shelfs"]["components"];

	for (int i = 0; i < shelfs_.size(); ++i) {
		Utensil* u = nullptr;

		jute::jValue shelf_ = jsonLevel["Shelfs"]["entities"][i]["content"];
		//Si contiene un utensilio, hago ese utensilio
		if (shelf_.size() > 0) {
			u = switchUten(shelf_[0].as_string(), pool_, player);
		}

		shelf_ = jsonLevel["Shelfs"]["entities"][i]["pos"];
		Shelf* s = makeShelf(u, player, shelf_);
		if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
			for (int c = 0; c < components.size(); ++c) {
				initializeComponent(components[c].as_string(), s);
			}
		}
	}
}

template <typename T>
Utensil* ShelfAdder::makeUtensil(std::array<Entity*, 2>& player, UtensilsPool* pool_)
{
	Utensil* u = new T(GIVETRANSPORT);
	u->setSize(Vector2D(jsonGeneral["Utensils"]["size"]["width"].as_int(), jsonGeneral["Utensils"]["size"]["height"].as_int()));
	return pool_->addUtensil(u);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

Utensil* ShelfAdder::switchUten(const string& ing, UtensilsPool* pool_, std::array<Entity*, 2>& player)
{
	Utensil* u = nullptr;
	switch (str2int(ing.c_str()))
	{
	case str2int("knife"):
		u = ADD(Knife);
		break;
	case str2int("mace"):
		u = ADD(Knife);
		break;
	default:
		break;
	}
	return u;
}

Shelf* ShelfAdder::makeShelf(Utensil* u, std::array<Entity*, 2>& player, jute::jValue& jsonShelf)
{
	Shelf* shelf = new Shelf(Vector2D(jsonShelf["x"].as_int(), jsonShelf["y"].as_int()), u, GIVETRANSPORT, emPlayState);
	emPlayState->addToGroup(shelf, CASTID(jsonGeneral["Shelf"]["Layer"].as_int()));
	emPlayState->addEntity(shelf);
	shelf->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), shelf);
	return shelf;
}


//La cadena (component) no puede superar 10 caracteres
void ShelfAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}
