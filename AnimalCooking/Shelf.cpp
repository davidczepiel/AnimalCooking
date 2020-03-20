#include "Shelf.h"


Shelf::Shelf(Pickable* c, Transport* p1, Transport* p2, EntityManager* mng):Entity(SDLGame::instance(),mng),Interactive(p1, p2),content(c) {
	addComponent<ShelfViewer>(this);
	if (content != nullptr)
		contentType = Resources::PickableType::Utensil;
	else
		contentType = Resources::PickableType::none;
}


void Shelf::action1(int id) {
	Transport* player;
	Resources::PickableType onPlayerHands;
	 //Dependiendo del numero que me ha llegado trabajare con el player1 o el player2
	if (id == 0)player = player1_;
	else player = player2_;
	//Sabiendo con quien interactuo le pido lo que tiene en las manos
	onPlayerHands = player->getObjectTypeInHands();
	Swap(player, onPlayerHands);
}

void Shelf::Swap(Transport* player, Resources::PickableType onPlayerHands) {
	Pickable* c = content;
	//Segun lo que tenga en las manos
	switch (onPlayerHands) {
		//SI no tiene nada, le paso mi contenido, diciendole de que tipo es y me quedo con nada
	case Resources::PickableType::none:
		player->pick(content, contentType);
		content = nullptr;
		contentType = Resources::PickableType::none;
		break;
		//Si tiene comida. SI Y SOLO SI tengo un plato, lo añado a este y le digo al player que lo suelte
	case Resources::PickableType::Food:
		if (contentType == Resources::PickableType::Dish) {
			static_cast<Dish*>(content)->addFood(static_cast<Food*>(player->getObjectInHands()));
			player->drop(false);
		}
		break;
		//En caso de que tenga o un plato o un utensilio hago un intercambio
	default:
		content = player->getObjectInHands();
		player->drop(false);
		player->pick(c,contentType);
		contentType = onPlayerHands;
		break;
	}
}