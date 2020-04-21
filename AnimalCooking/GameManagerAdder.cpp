#include "GameManagerAdder.h"
#include "GameLogic.h"
#include "UtensilsPool.h"
#include "FoodPool.h"
#include "IngredientsPool.h"
#include "Manager.h"
#include "CollisionsSystem.h"

GameManagerAdder::GameManagerAdder(Entity* gameManager,EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral,
	std::array<Entity*, 2>& player, UtensilsPool* utensilpool_, FoodPool* fp, IngredientsPool* ip, int casilla)
{
	GameLogic* glogic = gameManager->addComponent<GameLogic>();
	gameManager->addComponent<GameControl>(GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), utensilpool_, fp,ip,casilla);
	glogic->setUtensilsPool(utensilpool_);
	glogic->setIngredientPool(ip);

	initializeCollisionSystem(gameManager->addComponent<CollisionsSystem>(), player, ip);

	jute::jValue components = jsonLevel["GameManager"]["components"];
	for (int c = 0; c < components.size(); ++c) {
		initializeComponent(components[c].as_string(), gameManager);
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void GameManagerAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}

void GameManagerAdder::initializeCollisionSystem(CollisionsSystem* colSystem, std::array<Entity*, 2>& player, IngredientsPool* ip)
{
	colSystem->addCollider(GETCMP2(player[0], Transform));
	colSystem->addCollider(GETCMP2(player[1], Transform));

	for (auto& i : ip->getPool()) {
		colSystem->addCollider(i);
	}
}
