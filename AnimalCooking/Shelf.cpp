#include "Shelf.h"


Shelf::Shelf(Pickable* c, Transport* p1, Transport* p2) :Interactive(p1, p2) {
	content = c;
	addComponent<ShelfViewer>(this);
}

void Shelf::Swap(int id) {
	//Intercambia los contenidos de la repisa y las manos de cualquiera de los players
	//Sin importar que tenga algo o sea nullptr tanto la repisa como el player
	Pickable* p = content;
	if (id == 0) {
		if (dynamic_cast<Utensil*>(player1_->getObjectInHands()) != nullptr || dynamic_cast<Dish*>(player1_->getObjectInHands()) != nullptr) {
			content = player1_->getObjectInHands();
			player1_->pick(p);
			p->interactive(0);
		}
	}
	else {
		if (dynamic_cast<Utensil*>(player2_->getObjectInHands()) != nullptr || dynamic_cast<Dish*>(player2_->getObjectInHands()) != nullptr) {
			content = player2_->getObjectInHands();
			player2_->pick(p);
			p->interactive(1);
		}
	}
	//En casod de que sea algo, lo pongo justo encima mio en el centro para que renderice ahi
	if (content != nullptr) {
		content->setPos(position_ + Vector2D(size_.getX() / 2, size_.getY() / 2));
		Utensil* u = dynamic_cast<Utensil*>(content);
		if (u != nullptr)
			u->drop(false);
	}
}

void Shelf::interactive(int id) {
	Swap(id);
}