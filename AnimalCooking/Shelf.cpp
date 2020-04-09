#include "Shelf.h"


Shelf::Shelf(Vector2D pos, Pickable* c, Transport* p1, Transport* p2, EntityManager* mng) :Entity(SDLGame::instance(), mng), Interactive(p1, p2), content(c) {
	addComponent<ShelfViewer>(this);
	position_ = pos;
	size_ = Vector2D(128, 128);
	if (content != nullptr) {
		contentType = Resources::PickableType::Utensil;
		content->setPos(Vector2D(position_.getX() + (size_.getX() / 2 - content->getSize().getX() / 2),
			position_.getY() + (size_.getY() / 2 - content->getSize().getY() / 2)));
		content->setCanInteract(false);
	}
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
	if (content != nullptr) {
		content->setPos(Vector2D(position_.getX() + (size_.getX() / 2 - content->getSize().getX() / 2),
			position_.getY() + (size_.getY() / 2 - content->getSize().getY() / 2)));
		content->setCanInteract(false);
	}

}


void Shelf::action2(int id)
{
	cout << "Selector de platos" << endl;
	if (contentType == Resources::PickableType::Dish)
	{
		static_cast<Dish*>(content)->nextFood();
	}
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
		//Si tiene comida. SI Y SOLO SI tengo un plato, lo a�ado a este y le digo al player que lo suelte
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
		player->pick(c, contentType);
		contentType = onPlayerHands;
		break;
	}
}