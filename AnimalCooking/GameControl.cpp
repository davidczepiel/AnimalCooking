#include "GameControl.h" 
#include "Ingredient.h"  
GameControl::GameControl() : Component(ecs::GameControl)
{
}


void GameControl::newIngredient() {
	double y = (game_->getWindowHeight() / 4) * game_->getRandGen()->nextInt(1, 4);
	Ingredient* ing = new Tomato(); //Cambiar por un metodo newIngType que haga un random del enum y con un switch crea un ingrediente alatorio  
	ing->setTransform(50, 50, Vector2D(game_->getWindowWidth() + 50, y), Vector2D(-10, 0));
	ingPool_->addIngredient(ing);
	ing = nullptr;
}

void GameControl::newFood(Resources::FoodType type, Vector2D pos) {     //llamar al metodo foodpool para crear uno nuevo de tipo type y pos 
	Food* f;
	switch (type) {
	case(Resources::FoodType::SlicedTomato):
		f = new SlicedTomato(pos);
		break;
	default:
			f = new SlicedTomato(pos);
		break;
	}
	foodPool->AddFood(f);
}

