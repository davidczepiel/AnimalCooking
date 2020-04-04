#include "LevelInitializer.h"
#include "Manager.h"
#include "PlayersAdder.h"
#include "IngAdder.h"
#include "FoodPoolAdder.h"
#include "UtensilsAdder.h"

#include "ScreenLoader.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

const string rutaNivel = "../AnimalCooking/resources/cfg/nivel";
const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";

LevelInitializer::LevelInitializer(EntityManager* em, Resources::Level level, ScreenLoader* sL) : emPlaystate(em), players(), sL(sL)
{
	string ruta_ = rutaNivel + std::to_string(level) + ".cfg";

	jsonLevel = jute::parser::parse_file(ruta_); // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jsonGeneral = jute::parser::parse_file(rutaGeneral); // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	initialize_players();
	initialize_ingredientsPool();
	initialize_foodPool();
	initialize_utensilPool();
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
	Entity* foodPool = emPlaystate->addEntity();
	emPlaystate->addToGroup(foodPool, CASTID(jsonGeneral["Foods"]["Layer"].as_int()));

	FoodPoolAdder(foodPool, jsonLevel, jsonGeneral, players);
	sL->updateLength();
}

void LevelInitializer::initialize_utensilPool()
{
	//EntityUtensilPool----------------------------------------
	Entity* utensil = emPlaystate->addEntity();
	emPlaystate->addToGroup(utensil, CASTID(jsonGeneral["Utensils"]["Layer"].as_int()));

	UtensilsAdder(utensil, jsonLevel, jsonGeneral, players);
}
