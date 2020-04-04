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


#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

const string rutaNivel = "../AnimalCooking/resources/cfg/nivel";
const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";

LevelInitializer::LevelInitializer(EntityManager* em, Resources::Level level, ScreenLoader* sL) : emPlaystate(em), players(), sL(sL)
{
	string ruta_ = rutaNivel + std::to_string(level - 1) + ".cfg";

	jsonLevel = jute::parser::parse_file(ruta_); // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jsonGeneral = jute::parser::parse_file(rutaGeneral); // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	initialize_players();
	initialize_ingredientsPool();
	initialize_foodPool();
	initialize_utensilPool();
	initialize_cookersPool();
	initialize_shelfs();
	initialize_sinks();
	initialize_bin();
	initialize_dishes();
}


void LevelInitializer::initialize_players()
{
	for (int i = 0; i < players.size(); ++i) {
		players[i] = emPlaystate->addEntity();
		emPlaystate->addToGroup(players[i], CASTID(jsonGeneral["Players"]["Layer"].as_int()));
	}

	PlayersAdder(players, jsonLevel, jsonGeneral);

	sL->updateLength();
}

void LevelInitializer::initialize_ingredientsPool()
{
	//Ingredientes----------------------------------------
	ingPoolEntity_ = emPlaystate->addEntity();
	emPlaystate->addToGroup(ingPoolEntity_, CASTID(jsonGeneral["Ingredientes"]["Layer"].as_int()));

	IngAdder(ingPoolEntity_, jsonLevel, jsonGeneral);
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

	CookersAdder(cookers, jsonLevel, jsonGeneral, players, GETCMP2(foodPool, FoodPool));
	sL->updateLength();
}

void LevelInitializer::initialize_shelfs()
{
	ShelfAdder(emPlaystate, jsonLevel, jsonGeneral, players, GETCMP2(utensil, UtensilsPool));

	sL->updateLength();
}

void LevelInitializer::initialize_sinks()
{
	SinkAdder(emPlaystate, jsonLevel, jsonGeneral, players);

	sL->updateLength();
}

void LevelInitializer::initialize_bin()
{
	BinAdder(emPlaystate, jsonLevel, jsonGeneral, players);

	sL->updateLength();
}

void LevelInitializer::initialize_dishes()
{
	////Platera---------------------------------------
	//Entity* poolPlatos = stage->addEntity();
	//stage->addToGroup(poolPlatos, ecs::Layer2);
	//DishPool* dp =poolPlatos->addComponent<DishPool>();
	//poolPlatos->addComponent<DishMotion>();
	//poolPlatos->addComponent<DishViewer>();

	///*vector<Interactive*>* d = &reinterpret_cast<vector<Interactive*>&>(dp->getDishes());
	//poolPlatos->addComponent<SelectorPopUp>(d, GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
	//	GETCMP2(player, Selector), GETCMP2(player, Selector), GETCMP2(player, Transport), GETCMP2(player, Transport));*/

	//DishStack* dish = new DishStack(Vector2D(128*4,0),10,tp,tp,stage,dp);
	//dish->addComponent<SelectorPopUpEntity>(GETCMP2(player, InteractionRect), GETCMP2(player, InteractionRect),
	//	GETCMP2(player, Selector), GETCMP2(player, Selector), dish);
	//stage->addEntity(dish);
	//stage->addToGroup(dish, ecs::GroupID::Layer1);

}
