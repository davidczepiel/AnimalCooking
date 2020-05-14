#include "LevelInitializer.h"
#include "ScreenLoader.h"
#include "Manager.h"

#include "PlayersAdder.h"
#include "IngAdder.h"
#include "FoodPoolAdder.h"
#include "UtensilsAdder.h"
#include "ShelfAdder.h"
#include "CookersAdder.h"
#include "SinkAdder.h"
#include "BinAdder.h"
#include "DishAdder.h"
#include "GameManagerAdder.h"
#include "FoodGiverAdder.h"
#include "CollisionsSystem.h"
#include "FeedBack.h"
#include "TimerViewer.h"
#include "IngredientInitializer.h"
#include "OrderAdder.h"
#include "WallAdder.h"
#include "AdversityManager.h"
#include "MultipleAdversityManager.h"

#include "SDLGame.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

const string rutaNivel = "../AnimalCooking/resources/cfg/nivel";


LevelInitializer::LevelInitializer(EntityManager* em, int level, ScreenLoader* sL) : emPlaystate(em), players(), sL(sL)
{
	string ruta_ = rutaNivel + std::to_string(level - 1) + ".cfg";

	jsonLevel = jute::parser::parse_file(ruta_); // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jsonGeneral = SDLGame::instance()->getJsonGeneral();
	
	casillaX = SDLGame::instance()->getCasillaX();
	casillaY = SDLGame::instance()->getCasillaY();
	
	offsetX = casillaX * 0.2;
	offsetY = casillaY * 0.2;
	


	initialize_players();
	initialize_ingredientsPool();
	initialize_foodPool();
	initialize_utensilPool();
	initialize_timerViewer();
	initialize_cookersPool();
	initialize_shelfs();
	initialize_sinks();
	initialize_bin();
	initialize_dishes();
	initialize_gameManager();
	initialize_foodGivers();
	initialize_feedback();
	initialize_levelIngredients();
	initialize_clients();
	initialize_colSystem();
	initialize_walls();
	initialize_adversities();
}

void LevelInitializer::initialize_players()
{
	for (int i = 0; i < players.size(); ++i) {
		players[i] = emPlaystate->addEntity();
		emPlaystate->addToGroup(players[i], CASTID(jsonGeneral["Players"]["Layer"].as_int()));
	}

	PlayersAdder(players, jsonLevel, jsonGeneral, casillaX,casillaY);

	sL->updateLength();
}

void LevelInitializer::initialize_ingredientsPool()
{
	//Ingredientes----------------------------------------
	ingPoolEntity_ = emPlaystate->addEntity();
	emPlaystate->addToGroup(ingPoolEntity_, CASTID(jsonGeneral["Ingredientes"]["Layer"].as_int()));

	IngAdder(ingPoolEntity_, jsonLevel, jsonGeneral, GETCMP2(players[0], Transform), GETCMP2(players[1], Transform)/*, casilla*/);
	sL->updateLength();
}

void LevelInitializer::initialize_foodPool()
{
	//EntityFoodPool----------------------------------------
	foodPool = emPlaystate->addEntity();
	emPlaystate->addToGroup(foodPool, CASTID(jsonGeneral["Foods"]["Layer"].as_int()));

	FoodPoolAdder(foodPool, jsonLevel, jsonGeneral, players);
	sL->updateLength();
}

void LevelInitializer::initialize_utensilPool()
{
	//EntityUtensilPool----------------------------------------
	utensil = emPlaystate->addEntity();
	emPlaystate->addToGroup(utensil, CASTID(jsonGeneral["Utensils"]["Layer"].as_int()));

	UtensilsAdder(utensil, jsonLevel, jsonGeneral, players);
	sL->updateLength();
}

void LevelInitializer::initialize_cookersPool()
{
	cookerPool = emPlaystate->addEntity();
	emPlaystate->addToGroup(cookerPool, CASTID(jsonGeneral["Cookers"]["Layer"].as_int()));

	CookersAdder(cookerPool, jsonLevel, jsonGeneral, players, GETCMP2(foodPool, FoodPool), casillaX,casillaY);

	interactives_.insert(interactives_.end(), GETCMP2(cookerPool, CookerPool)->getPool().begin(), GETCMP2(cookerPool, CookerPool)->getPool().end());

	sL->updateLength();
}

void LevelInitializer::initialize_timerViewer()
{
	Entity* timersViewer = emPlaystate->addEntity();
	tv_ = timersViewer->addComponent<TimerViewer>();
	emPlaystate->addToGroup(timersViewer, ecs::GroupID::ui);

	SDLGame::instance()->setTimersViewer(timersViewer);

	sL->updateLength();
}

void LevelInitializer::initialize_shelfs()
{
	ShelfAdder sa = ShelfAdder(emPlaystate, jsonLevel, jsonGeneral, players, GETCMP2(utensil, UtensilsPool), casillaX,casillaY);

	interactives_.insert(interactives_.end(), sa.getInteractives().begin(), sa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_sinks()
{
	SinkAdder sa = SinkAdder(emPlaystate, jsonLevel, jsonGeneral, players, casillaX,casillaY);

	interactives_.insert(interactives_.end(), sa.getInteractives().begin(), sa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_bin()
{
	BinAdder ba = BinAdder(emPlaystate, jsonLevel, jsonGeneral, players, casillaX,casillaY);

	interactives_.insert(interactives_.end(), ba.getInteractives().begin(), ba.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_dishes()
{
	DishAdder da = DishAdder(emPlaystate, jsonLevel, jsonGeneral, players, GETCMP2(foodPool, FoodPool), casillaX,casillaY);

	interactives_.insert(interactives_.end(), da.getInteractives().begin(), da.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_gameManager()
{
	gameManager = emPlaystate->addEntity();
	GameManagerAdder(gameManager, emPlaystate, jsonLevel, jsonGeneral, players,
		GETCMP2(utensil, UtensilsPool), GETCMP2(foodPool, FoodPool), GETCMP2(ingPoolEntity_, IngredientsPool), casillaX,casillaY, offsetX,offsetY, tv_);

	emPlaystate->addToGroup(gameManager, CASTID(jsonGeneral["LevelTimer"]["Layer"].as_int()));

	sL->updateLength();
}

void LevelInitializer::initialize_foodGivers()
{
	FoodGiverAdder fa = FoodGiverAdder(emPlaystate, jsonLevel, jsonGeneral, players, gameManager, casillaX,casillaY);

	interactives_.insert(interactives_.end(), fa.getInteractives().begin(), fa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_colSystem()
{
	//Players e ingredientes se inicializan en el initialize_gameManager
	CollisionsSystem* col = GETCMP2(gameManager, CollisionsSystem);
	for (auto& i : interactives_) {
		col->addCollider(i);
	}

	sL->updateLength();
}

void LevelInitializer::initialize_feedback()
{
	Entity* feedbackEntity = emPlaystate->addEntity();
	feedbackEntity->addComponent<FeedBack>(players.at(0)->getComponent<Selector>(ecs::Selector), players.at(1)->getComponent<Selector>(ecs::Selector));
	emPlaystate->addToGroup(feedbackEntity, CASTID(jsonGeneral["FeedBack"]["Layer"].as_int()));

	sL->updateLength();
}

void LevelInitializer::initialize_levelIngredients()
{
	//Le decimos al GameControl que tipos de ingredientes van a aparecer en el nivel actual
	IngredientInitializer(jsonLevel, GETCMP2(gameManager, GameControl));

	sL->updateLength();
}

void LevelInitializer::initialize_clients()
{
	OrderAdder oa = OrderAdder(emPlaystate, jsonLevel, jsonGeneral, players, gameManager, casillaX,casillaY, tv_);

	interactives_.insert(interactives_.end(), oa.getInteractives().begin(), oa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_walls()
{
	WallAdder(emPlaystate, jsonLevel, jsonGeneral, GETCMP2(gameManager, CollisionsSystem), players, casillaX,casillaY, offsetX,offsetY);

	sL->updateLength();
}

void LevelInitializer::initialize_adversities()
{
	Entity* adversityManager = emPlaystate->addEntity();
	//AdversityManager de una sola adversidad
	/*adversityManager->addComponent<AdversityManager>(GETCMP2(players[0], Transform), GETCMP2(players[1], Transform), nullptr, GETCMP2(ingPoolEntity_, IngredientsPool), GETCMP2(utensil, UtensilsPool));
	GETCMP2(adversityManager, AdversityManager)->loadAdversity(ecs::AdversityID::RainAdversity);
	GETCMP2(gameManager, GameControl)->getAdversityTime()->setTime(5000);
	GETCMP2(gameManager, GameControl)->setAdvMngr(GETCMP2(adversityManager, AdversityManager));*/
	MultipleAdversityManager* mam = adversityManager->addComponent<MultipleAdversityManager>(GETCMP2(players[0], Transform), GETCMP2(players[1], Transform), GETCMP2(cookerPool, CookerPool), GETCMP2(ingPoolEntity_, IngredientsPool), GETCMP2(utensil, UtensilsPool));
	//mam->setTimerTime(ecs::AdversityID::RainAdversity,3000);
	//mam->setTimerTime(ecs::AdversityID::HookAdversity, 11000);
	mam->setTimerTime(ecs::AdversityID::PlaneAdversity, 5000);
	//mam->setTimerTime(ecs::AdversityID::CookersAdversity, 9000);

	emPlaystate->addToGroup(adversityManager, ecs::GroupID::topLayer);
	
	sL->updateLength();
}

