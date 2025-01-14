#include "GameControl.h" 
#include "Ingredient.h"  
#include "GameConfig.h"

GameControl::GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp, IngredientsPool* ip, int levelMaxIngredients) : 
	Component(ecs::GameControl),
	utensilsPool(u), 
	foodPool(fp), 
	tP1(p1), 
	tP2(p2), 
	ingPool_(ip), 
	levelIngType(), 
	justStarted(true), 
	indexType(0), 
	ingToMake_(),
	maxIngr(levelMaxIngredients)
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
		//Cuando empieza el nivel, al pasar x tiempo aparecen los ingredientes
		if (timer.isTimerEnd())
		{
			if (maxIngr > ingPool_->getPool().size()) {
				if (indexType < levelIngType.size()) makeIngredient(newIngType((levelIngType[indexType])));
				else makeIngredient(newIngType(chooseIng()));
				indexType++;
			}
			else justStarted = false;
			timer.timerReset();
			timer.timerStart();
		}
		else timer.update();
	}
	else {
		if (!ingToMake_.empty()) {
			auto it = ingToMake_.begin();
			while (it != ingToMake_.end()) {
				if (game_->getTime() - *it > 5000) {
					makeIngredient(newIngType(chooseIng()));
					ingToMake_.erase(it++);
				}
				else ++it;
			}
		}
	}
}

void GameControl::newIngredient()
{
	ingToMake_.push_back(game_->getTime());
}

//void GameControl::newIngredient(Resources::IngredientType i) 
//{
//	ingToMake_.push_back(game_->getTime(), i));
//}

void GameControl::makeIngredient(Ingredient* ing)
{
	jute::jValue& jsonGeneral = game_->getJsonGeneral();
	ing->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * SDLGame::instance()->getCasillaX(),
		jsonGeneral["Ingredientes"]["size"]["height"].as_double() * SDLGame::instance()->getCasillaY());

	double y = game_->getRandGen()->nextInt(0, 5 * SDLGame::instance()->getCasillaY());

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
		i = new Tomato(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::carrot:
		i = new Carrot(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::lettuce:
		i = new Lettuce(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::mushroom:
		i = new Mushroom(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::sausage:
		i = new Sausage(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::chicken:
		i = new Chicken(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::meat:
		i = new Meat(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::potato:
		i = new Potato(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::onion:
		i = new Onion(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::clam:
		i = new Clam(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::cheese:
		i = new Cheese(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::fish:
		i = new Fish(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::snowman:
		i = new SnowMan(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::avocado:
		i = new Avocado(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
		break;
	case Resources::IngredientType::salmon:
		i = new Salmon(GETTRANSFORM(tP1), GETTRANSFORM(tP2));
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

		if(ingsInScene.find(ing->getType()) != ingsInScene.end()) ++ingsInScene.find(ing->getType())->second;		
	}

	Resources::IngredientType lessIng = levelIngType[0];
	//Buscar el ingrediente con menos apariciones
	size_t min = SIZE_MAX;
	for (auto ings : ingsInScene) {
		if (ings.second < min) {
			min = ings.second;
			lessIng = ings.first;
		}
	}
	if(min == 0) return lessIng; //Si no est� ese ingrediente, aparece
	else { //Si todos los ingredientes aparecen una vez, se elige de entre los que menos haya uno (con +1 de rango) al azar
		vector<Resources::IngredientType> lista;
		lista.reserve(levelIngType.size());

		for (auto ings : ingsInScene) {
			if (ings.second <= min + 1) {
				lista.emplace_back(ings.first);
			}
		}

		return lista[game_->getRandGen()->nextInt(0, lista.size())];
	}
}

void GameControl::newFood(Food* f, Vector2D pos) {
	foodPool->AddFood(f);
	f->onFloor();
	f->setPos(pos);
	f->setTransports(tP1, tP2);
	newIngredient(); //al matar un ingrediente aparece otro
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
	case(Resources::FoodType::Nori):
		f = new Nori(pos, tP1, tP2);
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

