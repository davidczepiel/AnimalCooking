#include "Shelf.h"


Shelf::Shelf(Pickable* c, Transport* p1, Transport* p2) :Interactive(p1, p2) {
	content = c;
	addComponent<ShelfViewer>(this);
	if (content != nullptr)
		utensil = true;
	else
		utensil = false;
	dish = false;
}

void Shelf::SwapDish(int id) {
	Pickable* c = content;
	Resources::PickableType p1 = player1_->getObjectTypeInHands();
	Resources::PickableType p2 = player1_->getObjectTypeInHands();
	//////////////////////////PLayer 1
	if (id == 0) {
		switch (p1) {
		case(Resources::PickableType::none):
			dish = false;
			player1_->pick(content, Resources::PickableType::Dish);
			content = nullptr;
			break;
		case(Resources::PickableType::Food):
			static_cast<Dish*>(content)->addFood(static_cast<Food*>(player1_->getObjectInHands()));
			break;
		case (Resources::PickableType::Dish) :
			content = player1_->getObjectInHands();
			player1_->drop(false);
			player1_->pick(c, Resources::PickableType::Dish);
			break;
		case (Resources::PickableType::Utensil):
			content = player1_->getObjectInHands();
			player1_->drop(false);
			player1_->pick(c, Resources::PickableType::Dish);
			dish = false;
			utensil = true;
			break;
		}
	}
	////////////////////////////Player 2
	else {
		switch (p2) {
		case(Resources::PickableType::none):
			dish = false;
			player2_->pick(content, Resources::PickableType::Dish);
			content = nullptr;
			break;
		case(Resources::PickableType::Food):
			static_cast<Dish*>(content)->addFood(static_cast<Food*>(player2_->getObjectInHands()));
			break;
		case (Resources::PickableType::Dish):
			content = player2_->getObjectInHands();
			player2_->drop(false);
			player2_->pick(c, Resources::PickableType::Dish);
			break;
		case (Resources::PickableType::Utensil):
			content = player2_->getObjectInHands();
			player2_->drop(false);
			player2_->pick(c, Resources::PickableType::Dish);
			dish = false;
			utensil = true;
			break;
		}
	}
}

void Shelf::SwapUtensil(int id) {
	Pickable* c = content;
	Resources::PickableType p1 = player1_->getObjectTypeInHands();
	Resources::PickableType p2 = player1_->getObjectTypeInHands();
	////////////////////////Si lo que tengo es un utensilio
	if (id == 0) {
		if (p1 == Resources::PickableType::none) {   //SI no tiene nada, que se lleve mi utensilio
			player1_->pick(content, Resources::PickableType::Utensil);
			utensil = false;
			content = nullptr;
		}
		else if (p1 != Resources::PickableType::Food) { //SI tiene algo, intercambiamos. SIEMPRE Y CUANDO NO SEA UNA FOOD
			content = player1_->getObjectInHands();
			if (p1 == Resources::PickableType::Dish) { //Si hemos intercambiado y tenía un plato, preparo mis bools
				dish = true; utensil = false;
			}

			player1_->drop(false);
			player1_->pick(c, Resources::PickableType::Utensil);
		}
	}
	else {
		if (p2 == Resources::PickableType::none) {   //SI no tiene nada, que se lleve mi utensilio
			player2_->pick(content, Resources::PickableType::Utensil);
			utensil = false;
			content = nullptr;
		}
		else if (p2 != Resources::PickableType::Food) { //SI tiene algo, intercambiamos. SIEMPRE Y CUANDO NO SEA UNA FOOD
			content = player2_->getObjectInHands();
			if (p2 == Resources::PickableType::Dish) { //Si hemos intercambiado y tenía un plato, preparo mis bools
				dish = true; utensil = false;
			}
			player2_->drop(false);
			player2_->pick(c, Resources::PickableType::Utensil);
		}
	}
}


void Shelf::Save(int id) {
	// Pregunto lo que tiene cada uno de los players
	Resources::PickableType p1 = player1_->getObjectTypeInHands();
	Resources::PickableType p2 = player1_->getObjectTypeInHands();
	///////////////////////PLAYER 1
	if (id == 0 && p1 != Resources::PickableType::none && p1 != Resources::PickableType::Food) { //Tiene que tener algo y ademas que nos ea foodç

		if (p1 == Resources::PickableType::Dish)  //Si es un plato
			dish = true;
		else       //Si es un utensilio
			utensil = true;

		//Me llevo lo que tenga y le aviso
		content = player1_->getObjectInHands();
		player1_->drop(false);
	}
	//////////////////////////////PLAYER 2
	else if (id == 1 && p2 != Resources::PickableType::none && p2 != Resources::PickableType::Food) { //Tiene que tener algo y ademas que nos ea food
		
		if (p2 == Resources::PickableType::Dish) //Si es un plato
			dish = true;
		else                     //Si es un utensilio
			utensil = true;

		//Me llevo lo que tenga y le aviso
		content = player2_->getObjectInHands();
		player2_->drop(false);
	}
}

void Shelf::interactive(int id) {
	if (content == nullptr)
		Save(id);
	else {
		if (utensil)SwapUtensil(id);
		else SwapDish(id);
	}
}