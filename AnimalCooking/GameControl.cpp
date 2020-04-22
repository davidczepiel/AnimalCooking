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
	f->onFloor();
	f->setPos(pos);
	f->setTransports(tP1, tP2);
}

Food* GameControl::newFood(Resources::FoodType type, Vector2D pos) {     //llamar al metodo foodpool para crear uno nuevo de tipo type y pos 
	Food* f;
	switch (type) {

		///////////KNIFE
	case(Resources::FoodType::SlicedTomato):
		f = new SlicedTomato(pos,tP1,tP2);
		break;
	case(Resources::FoodType::SlicedCheese):
		f = new SlicedCheese(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedCarrot):
		f = new SlicedCarrot(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedMeat):
		f = new SlicedMeat(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedLettuce):
		f = new SlicedLettuce(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedSausage):
		f = new SlicedSausage(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedMushroom):
		f = new SlicedMushroom(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedPotato):
		f = new SlicedPotato(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedOnion):
		f = new SlicedOnion(pos, tP1, tP2);
		break;
	case(Resources::FoodType::SlicedChicken):
		f = new SlicedTomato(pos, tP1, tP2);
		break;


		//////////////MACE
	case(Resources::FoodType::MashedTomato):
		f = new SlicedTomato(pos, tP1, tP2); ///Esto est� puesto para que no queje de que no se inicializa
		//f = new MashedTomato(pos);
		break;
	case(Resources::FoodType::MashedMeat):
		f = new MashedMeat(pos, tP1, tP2);
		break;
	case(Resources::FoodType::MashedMushroom):
		f = new MashedMushroom(pos, tP1, tP2);
		break;
	
		///////////////GRATER
	case(Resources::FoodType::GratedCheese):
		f = new GratedCheese(pos, tP1, tP2);
		break;

		///////////////NET
	case(Resources::FoodType::CaughtClam):
		f = new CaughtClam(pos, tP1, tP2);
		break;
	case(Resources::FoodType::CaughtFish):
		f = new CaughtFish(pos, tP1, tP2);
		break;
	case(Resources::FoodType::CaughtSausage):
		f = new CaughtSausage(pos, tP1, tP2);
		break;
	
		//////////////EMPTY
	default:
		f = new SlicedTomato(pos, tP1, tP2); // Para que no queje
		break;
	}
	foodPool->AddFood(f);
	f->onFloor();
	return f;
}

