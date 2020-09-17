#include "GameManagerAdder.h"
#include "GameLogic.h"
#include "UtensilsPool.h"
#include "FoodPool.h"
#include "IngredientsPool.h"
#include "Manager.h"
#include "CollisionsSystem.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "TimerViewer.h"
#include "GameControlLevelIngredientsChanger.h"

GameManagerAdder::GameManagerAdder(Entity* gameManager, EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral,
	std::array<Entity*, 2>& player, UtensilsPool* utensilpool_, FoodPool* fp, IngredientsPool* ip, int casillaX, int casillaY, const double offsetX, const double offsetY, TimerViewer* tv)
{
	initializeCollisionSystem(gameManager->addComponent<CollisionsSystem>(casillaX, casillaY, 8.5 * casillaX + offsetY, 7 * casillaY), player, ip);

	gameManager->addComponent<ScoreManager>();
	GameLogic* glogic = gameManager->addComponent<GameLogic>(tv);
	GameControl* gControl = gameManager->addComponent<GameControl>(GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), utensilpool_, fp, ip, jsonLevel["MaxIngredients"].as_int());

	GameControlLevelIngredientsChanger* changer_ = GETCMP2(ip->getEntity(), GameControlLevelIngredientsChanger);
	if (changer_ != nullptr) changer_->setGameControl(gControl);

	glogic->setIngredientPool(ip);

	ScoreViewer* sv = gameManager->addComponent<ScoreViewer>();
	sv->setPos(Vector2D(jsonGeneral["Score"]["pos"]["x"].as_double() * casillaX, jsonGeneral["Score"]["pos"]["y"].as_double() * casillaY));

	glogic->setLevelTimer(jsonLevel["LevelTimer"]["Time"].as_int() * 1000,
		Vector2D(jsonGeneral["LevelTimer"]["pos"]["x"].as_double() * casillaX, jsonGeneral["LevelTimer"]["pos"]["y"].as_double() * casillaY),
		Vector2D(jsonGeneral["LevelTimer"]["size"]["width"].as_double() * casillaX, jsonGeneral["LevelTimer"]["size"]["height"].as_double() * casillaX));

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
