#include "GameControl.h" 
#include "Ingredient.h"  
GameControl::GameControl(Transport* p1, Transport* p2, UtensilsPool* u, FoodPool* fp) : Component(ecs::GameControl)
{
	utensilsPool = u;
	foodPool = fp;
	tP1 = p1;
	tP2 = p2;
}


void GameControl::newIngredient() {
	double y = (game_->getWindowHeight() / 4) * game_->getRandGen()->nextInt(1, 4);
	Ingredient* ing = newIngType(); // Se crea un ingrediente nuevo aleatorio 
	ing->setTransform(50, 50, Vector2D(game_->getWindowWidth() + 50, y), Vector2D(-10, 0));
	ingPool_->addIngredient(ing);
	ing = nullptr;
}

Ingredient* GameControl::newIngType() {
	Ingredient* i;
	int random = SDLGame::instance()->getRandGen()->nextInt(1, 13);
	switch (random) {
	case 0:
		i = new Tomato();
		break;
	case 1:
		i = new Carrot();
		break;
	case 2:
		i = new Lettuce();
		break;
	case 3:
		i = new Mushroom();
		break;
	case 4:
		i = new Sausage();
		break;
	case 5:
		i = new Chicken();
		break;
	case 6:
		i = new Meat();
		break;
	case 7:
		i = new Potato();
		break;
	case 8:
		i = new Onion();
		break;
	case 9:
		i = new Clam();
		break;
	case 10:
		i = new Cheese();
		break;
	default:
		i = new Fish();
		break;
	}
	return i;
}

void GameControl::newFood(Food* f, Vector2D pos) {
	foodPool->AddFood(f);
	f->onDrop(true);
	f->setPos(pos);
	f->setTransports(tP1, tP2);
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

