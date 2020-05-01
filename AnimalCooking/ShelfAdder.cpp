#include "ShelfAdder.h"
#include "Shelf.h"
#include "SelectorPopUpEntity.h"
#include "Utensil.h"
#include "UtensilsPool.h"
#include "SDLRenderer.h"

#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)
#define ADD(t) makeUtensil<t>(player, pool_)
#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

ShelfAdder::ShelfAdder(EntityManager* emPlayState, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, UtensilsPool* pool_, const double casilla) :
	emPlayState(emPlayState), jsonGeneral(jsonGeneral), casillaLength(casilla)
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

		shelf_ = jsonLevel["Shelfs"]["entities"][i];
		Shelf* s = makeShelf(u, player, shelf_);
		for (int c = 0; c < components.size(); ++c) {//Si tiene algun componente extra en ese nivel
			initializeComponent(components[c].as_string(), s);
		}
	}
}

template <typename T>
Utensil* ShelfAdder::makeUtensil(std::array<Entity*, 2>& player, UtensilsPool* pool_)
{
	Utensil* u = new T(GIVETRANSPORT);
	u->setSize(Vector2D(jsonGeneral["Utensils"]["size"]["width"].as_double() * casillaLength,
		jsonGeneral["Utensils"]["size"]["height"].as_double() * casillaLength));
	timers_.push_back(u->getTimer());
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
		u = ADD(Mace);
		break;
	case str2int("grater"):
		u = ADD(Grater);
		break;
	case str2int("net"):
		u = ADD(Net);
		break;
	default:
		break;
	}
	return u;
}

Shelf* ShelfAdder::makeShelf(Utensil* u, std::array<Entity*, 2>& player, jute::jValue& jsonShelf)
{
	Vector2D pos = Vector2D(jsonShelf["pos"]["x"].as_double() * casillaLength, jsonShelf["pos"]["y"].as_double() * casillaLength);
	int t = 0;
	if (jsonShelf["texture"].as_string() == "top") {
		t = Resources::TextureId::EncimeraHorizConMantel + SDLGame::instance()->getRandGen()->nextInt(0, 2);
	}
	else if (jsonShelf["texture"].as_string() == "right") {
		t = Resources::TextureId::EncimeraVertConMantelDcha + SDLGame::instance()->getRandGen()->nextInt(0, 2) * 2;
	}
	else if (jsonShelf["texture"].as_string() == "left") {
		t = Resources::TextureId::EncimeraVertConMantelIzda + SDLGame::instance()->getRandGen()->nextInt(0, 2) * 2;
	}
	else if (jsonShelf["texture"].as_string() == "bottom") {
		t = Resources::TextureId::EncimeraAbajoConMantel + SDLGame::instance()->getRandGen()->nextInt(0, 2);
	}
	else if (jsonShelf["texture"].as_string() == "cornerRight") {
		t = Resources::TextureId::EncimeraVEsquinaInferiorDcha;
	}
	else { //CornerLeft
		t = Resources::TextureId::EncimeraVEsquinaSuperiorDcha;
	}
	Shelf* shelf = new Shelf(pos, u, GIVETRANSPORT, emPlayState, SDLGame::instance()->getTextureMngr()->getTexture(t));

	shelf->setSize(Vector2D(jsonGeneral["Shelf"]["size"]["width"].as_double() * casillaLength,
		jsonGeneral["Shelf"]["size"]["height"].as_double() * casillaLength));

	if (u != nullptr) shelf->setContentPos();

	emPlayState->addToGroup(shelf, CASTID(jsonGeneral["Shelf"]["Layer"].as_int()));
	emPlayState->addEntity(shelf);
	shelf->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), shelf);
	interactives_.push_back(shelf);
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