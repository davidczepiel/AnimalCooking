#include "FoodPoolAdder.h"
#include "Entity.h"
#include "LevelInitializer.h"
#include "SelectorPopUp.h"
#include "FoodViewer.h"
#include "FoodMotion.h"

FoodPoolAdder::FoodPoolAdder(Entity* foodPool, jute::jValue jsonLevel, jute::jValue jsonGeneral, std::array<Entity*, 2>& players, LevelInitializer* li) :
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
			li->initializeComponent(components[c].as_string(), foodPool);
		}
	}
}