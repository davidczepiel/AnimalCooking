#include "Sink.h"
Sink::Sink(Vector2D pos,Transport* p1, Transport* p2, EntityManager* mng) :Entity(SDLGame::instance(),mng), Interactive(p1, p2,nullptr), nTries(), cadence(333), lastTry() {
	addComponent<SinkViewer>(this);
	position_ = pos;
	size_ = Vector2D(128, 128);
	maxTries = SDLGame::instance()->getRandGen()->nextInt(3, 6);
}

Sink::~Sink() {
}

void Sink::action1(int iDp) {
	if (SDLGame::instance()->getTime() - lastTry < cadence) {
		++nTries;
		lastTry = SDLGame::instance()->getTime();
		//Dependiendo del numero que me llegue me trabajo con el player 1 o 2
		Transport* player;
		if (iDp == 0) player = player1_;
		else player = player2_;

		cout << "TRY CLEAN UP: " << nTries << endl;

		//Y SI Y SOLO SI tiene un utensilio le digo que se limpie
		if (nTries >= maxTries && player->getObjectTypeInHands() == Resources::PickableType::Utensil) {
			static_cast<Utensil*>(player->getObjectInHands())->cleanUp();
			nTries = 0;
			cout << "CLEAN" << endl;
		}	
	}
	else {
		nTries = 0;
		lastTry = SDLGame::instance()->getTime();
	}
}