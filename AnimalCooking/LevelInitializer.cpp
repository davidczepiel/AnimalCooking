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

#include "SDLGame.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

const string rutaNivel = "../AnimalCooking/resources/cfg/nivel";


LevelInitializer::LevelInitializer(EntityManager* em, Resources::Level level, ScreenLoader* sL) : emPlaystate(em), players(), sL(sL)
{
	string ruta_ = rutaNivel + std::to_string(level - 1) + ".cfg";

	jsonLevel = jute::parser::parse_file(ruta_); // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jsonGeneral = SDLGame::instance()->getJsonGeneral();

	casilla = SDLGame::instance()->getWindowHeight() / 9;
	offset = casilla * 0.2;
	SDLGame::instance()->setCasillaLength(casilla);

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
}

void LevelInitializer::initialize_players()
{
	for (int i = 0; i < players.size(); ++i) {
		players[i] = emPlaystate->addEntity();
		emPlaystate->addToGroup(players[i], CASTID(jsonGeneral["Players"]["Layer"].as_int()));
	}

	PlayersAdder(players, jsonLevel, jsonGeneral, casilla);

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
	Entity* cookers = emPlaystate->addEntity();
	emPlaystate->addToGroup(cookers, CASTID(jsonGeneral["Cookers"]["Layer"].as_int()));

	list<Timer*> aux = CookersAdder(cookers, jsonLevel, jsonGeneral, players, GETCMP2(foodPool, FoodPool), casilla).getTimers();
	timers_.insert(timers_.end(), aux.begin(), aux.end());

	interactives_.insert(interactives_.end(), GETCMP2(cookers, CookerPool)->getPool().begin(), GETCMP2(cookers, CookerPool)->getPool().end());

	sL->updateLength();
}

void LevelInitializer::initialize_timerViewer()
{
	Entity* timersViewer = emPlaystate->addEntity();
	timersViewer->addComponent<TimerViewer>();
	emPlaystate->addToGroup(timersViewer, ecs::GroupID::ui);

	SDLGame::instance()->setTimersViewer(timersViewer);

	sL->updateLength();
}

void LevelInitializer::initialize_shelfs()
{
	ShelfAdder sa = ShelfAdder(emPlaystate, jsonLevel, jsonGeneral, players, GETCMP2(utensil, UtensilsPool), casilla);

	list<Timer*> aux = sa.getTimers();
	timers_.insert(timers_.end(), aux.begin(), aux.end());

	interactives_.insert(interactives_.end(), sa.getInteractives().begin(), sa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_sinks()
{
	SinkAdder sa = SinkAdder(emPlaystate, jsonLevel, jsonGeneral, players, casilla);

	interactives_.insert(interactives_.end(), sa.getInteractives().begin(), sa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_bin()
{
	BinAdder ba = BinAdder(emPlaystate, jsonLevel, jsonGeneral, players, casilla);

	interactives_.insert(interactives_.end(), ba.getInteractives().begin(), ba.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_dishes()
{
	DishAdder da = DishAdder(emPlaystate, jsonLevel, jsonGeneral, players, GETCMP2(foodPool, FoodPool), casilla);

	interactives_.insert(interactives_.end(), da.getInteractives().begin(), da.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_gameManager()
{
	gameManager = emPlaystate->addEntity();
	GameManagerAdder(gameManager, emPlaystate, jsonLevel, jsonGeneral, players,
		GETCMP2(utensil, UtensilsPool), GETCMP2(foodPool, FoodPool), GETCMP2(ingPoolEntity_, IngredientsPool), casilla, offset);

	emPlaystate->addToGroup(gameManager, CASTID(jsonGeneral["LevelTimer"]["Layer"].as_int()));

	sL->updateLength();
}

void LevelInitializer::initialize_foodGivers()
{
	FoodGiverAdder fa = FoodGiverAdder(emPlaystate, jsonLevel, jsonGeneral, players, gameManager, casilla);

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
	OrderAdder oa = OrderAdder(emPlaystate, jsonLevel, jsonGeneral, players, gameManager, casilla);

	interactives_.insert(interactives_.end(), oa.getInteractives().begin(), oa.getInteractives().end());

	sL->updateLength();
}

void LevelInitializer::initialize_walls()
{
	WallAdder(emPlaystate, jsonLevel, jsonGeneral, GETCMP2(gameManager, CollisionsSystem), players, casilla, offset);

	sL->updateLength();
}

