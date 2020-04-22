#include "GameControl.h" 
#include "Ingredient.h"  

GameControl::GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp, IngredientsPool* ip, int casilla) : Component(ecs::GameControl), 
	utensilsPool(u),foodPool(fp),tP1(p1),tP2(p2),ingPool_(ip),levelIngType(),casillaLength(casilla)
{
	jsonGeneral = jute::parser::parse_file("../AnimalCooking/resources/cfg/general.cfg");

	timer.setTime(1000);
	timer.timerStart();
}


void GameControl::init()
{
	colSys_ = GETCMP1_(CollisionsSystem);
}

void GameControl::update()
{
	//Cuando empieza el nivel,al pasar x tiempo aparecen los ingredientes
	if (timer.isTimerEnd())
	{
		for (int i = 0; i < 4; i++)
		{
			newIngredient();
		}
		timer.timerReset();
	}
	else timer.update();
}

void GameControl::newIngredient() 
{   
	Ingredient* ing = newIngType(levelIngType[game_->getRandGen()->nextInt(0, levelIngType.size())]);  

	ing->setSize(jsonGeneral["Ingredientes"]["size"]["width"].as_double() * casillaLength,
		jsonGeneral["Ingredientes"]["size"]["height"].as_double() * casillaLength);
	double y = game_->getRandGen()->nextInt(ing->getHeight(), game_->getWindowHeight()/2+ing->getHeight());
	//double y = (game_->getWindowHeight() / 4) * game_->getRandGen()->nextInt(1, 4);
	//De momento aparecen con velocidad 0 y en el centro de la pantalla
    ing->setVel(Vector2D(0,0));
    ing->setPos(Vector2D(game_->getWindowWidth()/2, y));

	ingPool_->addIngredient(ing);
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

void GameControl::newFood(Food* f, Vector2D pos) {
	foodPool->AddFood(f);
	f->onDrop(true);
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
		//////////////EMPTY
	default:
		f = nullptr;
		break;
	}
	foodPool->AddFood(f);
	f->onDrop(true);
	return f;
}

