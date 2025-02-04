#include "DishAdder.h"
#include "Manager.h"
#include "SelectorPopUpEntity.h"
#include "DishStack.h"
#include "DishMotion.h"
#include "DishViewer.h"


#define CASTID(t) static_cast<ecs::GroupID>(t - 1)
#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)

DishAdder::DishAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral,
	std::array<Entity*, 2>& player, FoodPool* fp, const double casillaX, const double casillaY) :
	em(em)
{
	//DishPool
	Entity* poolPlatos = em->addEntity();
	em->addToGroup(poolPlatos, CASTID(jsonGeneral["Dish"]["Layer"].as_int()));
	dp = poolPlatos->addComponent<DishPool>();
	poolPlatos->addComponent<DishMotion>();
	poolPlatos->addComponent<DishViewer>();
	//Componentes extra
	jute::jValue components = jsonLevel["DishPool"]["components"];
	for (int i = 0; i < components.size(); ++i) {
		initializeComponent(components[i].as_string(), poolPlatos);
	}

	Texture* t = nullptr;
	if(jsonLevel["DishStack"]["texture"].as_string() == "BordeDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlateraBordeDerecha);
	else if (jsonLevel["DishStack"]["texture"].as_string() == "PlatosBordes") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatosBordes);
	else if (jsonLevel["DishStack"]["texture"].as_string() == "PlatosVer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatosVer);
	else if(jsonLevel["DishStack"]["texture"].as_string() == "PlatosVerDosBordes") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatosVerDosBordes);
	else if (jsonLevel["DishStack"]["texture"].as_string() == "PlatosBordeSoloDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlateraBordeSoloDerecha);
	else if (jsonLevel["DishStack"]["texture"].as_string() == "PlatosEsqSupDer") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatosEsqSupDer);
	else if (jsonLevel["DishStack"]["texture"].as_string() == "PlatosAislados") t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PlatosAislados);
	else t = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Platera);

	//DishStack
	DishStack* dish = new DishStack(Vector2D(jsonLevel["DishStack"]["pos"]["x"].as_double() * casillaX,
		jsonLevel["DishStack"]["pos"]["y"].as_double() * casillaY),
		jsonLevel["DishStack"]["maxDishes"].as_int(), GIVETRANSPORT, em, dp, fp,t);
	em->addEntity(dish);
	em->addToGroup(dish, CASTID(jsonGeneral["DishStack"]["Layer"].as_int()));

	dish->setDishSize(Vector2D(jsonGeneral["Dish"]["size"]["width"].as_double() * casillaX, jsonGeneral["Dish"]["size"]["height"].as_double() * casillaY));

	dish->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), dish);

	dish->setSize(Vector2D(jsonGeneral["DishStack"]["size"]["width"].as_double() * casillaX,
		jsonGeneral["DishStack"]["size"]["width"].as_double() * casillaY));

	dish->setHitboxSize(Vector2D(dish->getSize().getX(), dish->getSize().getY()));
	//Componentes extra
	components = jsonLevel["DishStack"]["components"];
	for (int i = 0; i < components.size(); ++i) {
		initializeComponent(components[i].as_string(), dish);
	}

	interactives_.push_back(dish);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void DishAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}