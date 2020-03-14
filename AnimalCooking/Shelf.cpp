#include "Shelf.h"


Shelf::Shelf(Transport* p1, Transport* p2) :Interactive(p1,p2), Component(ecs::Shelf) {
	content = nullptr;
	tr = GETCMP1_(Transform);
}


void Shelf::Swap(int id) {
	//Intercambia los contenidos de la repisa y las manos de cualquiera de los players
	//Sin importar que tenga algo o sea nullptr tanto la repisa como el player
		Pickable* p = content;
	if (id == 0) {
		content = player1_->getObjectInHands();
		player1_->pick(p);
	}
	else {
		content = player2_->getObjectInHands();
		player2_->pick(p);
	}
	//En casod de que sea algo, lo pongo justo encima mio en el centro para que renderice ahi
	if (content != nullptr)
		content->setPos(tr->getPos()+ Vector2D(tr->getW()/2,tr->getH()/2));
}

void Shelf::interactive(int id) {
	Swap(id);
}