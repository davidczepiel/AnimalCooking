#include "DishAdder.h"
#include "Manager.h"
#include "SelectorPopUpEntity.h"
#include "DishStack.h"
#include "DishMotion.h"
#include "DishViewer.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)
#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)

DishAdder::DishAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player,FoodPool* fp ,const double casillaLength) : em(em)
{
	//DishPool
	Entity* poolPlatos = em->addEntity();
	em->addToGroup(poolPlatos, CASTID(jsonGeneral["Dish"]["Layer"].as_int()));
	DishPool* dp = poolPlatos->addComponent<DishPool>();
	poolPlatos->addComponent<DishMotion>();
	poolPlatos->addComponent<DishViewer>();
	//Componentes extra
	jute::jValue components = jsonLevel["DishPool"]["components"];
	for (int i = 0; i < components.size(); ++i) {
		initializeComponent(components[i].as_string(), poolPlatos);
	}

	//DishStack
	DishStack* dish = new DishStack(Vector2D(jsonLevel["DishStack"]["pos"]["x"].as_double() * casillaLength,
		jsonLevel["DishStack"]["pos"]["y"].as_double() * casillaLength),
		jsonLevel["DishStack"]["maxDishes"].as_int(), GIVETRANSPORT, em, dp,fp);
	em->addEntity(dish);
	em->addToGroup(dish, CASTID(jsonGeneral["DishStack"]["Layer"].as_int()));

	dish->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), dish);

	dish->setSize(Vector2D(jsonGeneral["DishStack"]["size"]["width"].as_double() * casillaLength,
		jsonGeneral["DishStack"]["size"]["width"].as_double() * casillaLength));
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