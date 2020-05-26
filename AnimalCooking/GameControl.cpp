#include "GameControl.h" 
#include "Ingredient.h"  
#include "GameConfig.h"

GameControl::GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp, IngredientsPool* ip, int levelMaxIngredients) : Component(ecs::GameControl),
	utensilsPool(u),foodPool(fp),tP1(p1),tP2(p2),ingPool_(ip),levelIngType(), justStarted(true), indexType(0), maxIngr(levelMaxIngredients)
{
	timer.setTime(config::ING_STARTING_DELTA_TIME);
	timer.timerStart();
}


void GameControl::init()
{
	colSys_ = GETCMP1_(CollisionsSystem);
}

void GameControl::update()
{
	if (justStarted) {
		//Cuando empieza el nivel,al pasar x tiempo aparecen los ingredientes
		if (timer.isTimerEnd())
		{
			if (maxIngr > ingPool_->getPool().size()) {
				if (indexType < levelIngType.size()) newIngredient(levelIngType[indexType]);
				else newIngredient(chooseIng());
				indexType++;
			}
			else justStarted = false;
			timer.timerReset();
			timer.timerStart();
		}
		else timer.update();
	}
}

void GameControl::newIngredient() 
{   
	Ingredient* ing = newIngType(chooseIng());  

	jute::jValue& jsonGeneral = game_->getJsonGeneral();
	ing->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(),
		jsonGeneral["Ingredientes"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY());

	double y = ((game_->getRandGen()->nextInt(0, 3) * 2) + 1.5) * SDLGame::instance()->getCasillaY();

    ing->setVel(Vector2D(-1, game_->getRandGen()->nextInt(-1, 1) / 2.0));
    ing->setPos(Vector2D(game_->getWindowWidth() - jsonGeneral["Ingredientes"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(), y));
	ing->setMaxVel(config::AI_INGREDIENT_MAX_VEL);
	ingPool_->addIngredient(ing);
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::IngredientSpawned,0);
	colSys_->addCollider(ing);
	ing = nullptr;
}

void GameControl::newIngredient(Resources::IngredientType i) {
	Ingredient* ing = newIngType(i);

	jute::jValue& jsonGeneral = game_->getJsonGeneral();
	ing->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(),
		jsonGeneral["Ingredientes"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY());

	//double y = game_->getRandGen()->nextInt(ing->getHeight(), game_->getWindowHeight()/2+ing->getHeight());
	double y = ((game_->getRandGen()->nextInt(0, 3) * 2) + 1.5) * SDLGame::instance()->getCasillaY();

	ing->setVel(Vector2D(-1, game_->getRandGen()->nextInt(-1, 1) / 2.0));
	ing->setPos(Vector2D(game_->getWindowWidth() - jsonGeneral["Ingredientes"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(), y));
	ing->setMaxVel(config::AI_INGREDIENT_MAX_VEL);
	ingPool_->addIngredient(ing);
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::IngredientSpawned, 0);
	colSys_->addCollider(ing);
	ing = nullptr;
}

Ingredient* GameControl::newIngType(const Resources::IngredientType& iT) {

	Ingredient* i = nullptr;
	
	switch (iT)
	{
	case Resources::IngredientType::tomato:
		i = new Tomato();
		break;
	case Resources::IngredientType::carrot:
		i = new Carrot();
		break;
	case Resources::IngredientType::lettuce:
		i = new Lettuce();
		break;
	case Resources::IngredientType::mushroom:
		i = new Mushroom();
		break;
	case Resources::IngredientType::sausage:
		i = new Sausage();
		break;
	case Resources::IngredientType::chicken:
		i = new Chicken();
		break;
	case Resources::IngredientType::meat:
		i = new Meat();
		break;
	case Resources::IngredientType::potato:
		i = new Potato();
		break;
	case Resources::IngredientType::onion:
		i = new Onion();
		break;
	case Resources::IngredientType::clam:
		i = new Clam();
		break;
	case Resources::IngredientType::cheese:
		i = new Cheese();
		break;
	case Resources::IngredientType::fish:
		i = new Fish();
		break;
	default:
		break;
	}
	return i;
}

Resources::IngredientType GameControl::chooseIng()
{
	//Rellenar un diccionario con los ingredientes que hay en escena 
	map<Resources::IngredientType, size_t> ingsInScene;

	for (auto type : levelIngType) {
		ingsInScene.insert(make_pair(type, 0));
	}
	for (auto ing : ingPool_->getPool()) {
		++ingsInScene.find(ing->getType())->second;
	}


	vector<Resources::IngredientType> lista;
	lista.reserve(levelIngType.size());

	//Buscar el ingrediente con menos apariciones
	size_t min = SIZE_MAX;
	for (auto ings : ingsInScene) {
		if(ings.second < min){
			min = ings.second;
		}
	}
	for (auto ings : ingsInScene) {
		if (ings.second <= min + 1) {
			lista.emplace_back(ings.first);
		}
	}

	return lista[game_->getRandGen()->nextInt(0, lista.size())];
}

void GameControl::newFood(Food* f, Vector2D pos, Resources::IngredientType ingType) {
	foodPool->AddFood(f);
	f->onFloor();
	f->setPos(pos);
	f->setTransports(tP1, tP2);
	newIngredient(ingType); //al matar un ingrediente aparece otro
}

Food* GameControl::newFood(Resources::FoodType type, Vector2D pos) {     //llamar al metodo foodpool para crear uno nuevo de tipo type y pos 
	Food* f;
	switch (type) {

		//////////////FOOD GIVER
	case(Resources::FoodType::BreadBurger):
		f = new BreadBurger(pos, tP1, tP2);
		break;
	case(Resources::FoodType::BreadHotDog):
		f = new BreadHotDog(pos, tP1, tP2);
		break;
	case(Resources::FoodType::PizzaMass):
		f = new PizzaMass(pos, tP1, tP2);
		break;
	case(Resources::FoodType::Rice):
		f = new Rice(pos, tP1, tP2);
		break;
	case(Resources::FoodType::Dress):
		f = new Dress(pos, tP1, tP2);
		break;
		//////////////EMPTY
	default:
		f = nullptr;
		break;
	}
	foodPool->AddFood(f);
	//f->onFloor();
	return f;
}

