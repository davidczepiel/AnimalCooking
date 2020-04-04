#include "FoodPoolAdder.h"
#include "LevelInitializer.h"
#include "SelectorPopUp.h"
#include "FoodViewer.h"
#include "FoodMotion.h"


FoodPoolAdder::FoodPoolAdder(Entity* foodPool, jute::jValue jsonLevel, jute::jValue jsonGeneral, std::array<Entity*, 2>& players) :
	foodPool(foodPool), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	FoodPool* fp = foodPool->addComponent<FoodPool>();

	foodPool->addComponent<SelectorPopUp>(&reinterpret_cast<vector<Interactive*>&>(fp->getPool()), GETCMP2(players[0], InteractionRect), GETCMP2(players[1], InteractionRect),
		GETCMP2(players[0], Selector), GETCMP2(players[1], Selector), GETCMP2(players[0], Transport), GETCMP2(players[1], Transport));

	foodPool->addComponent<FoodMotion>();
	foodPool->addComponent<FoodViewer>();

	jute::jValue components = jsonLevel["IngredientsPool"]["components"];
	if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
		for (int c = 0; c < components.size(); ++c) {
			initializeComponent(components[c].as_string(), foodPool);
		}
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void FoodPoolAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}