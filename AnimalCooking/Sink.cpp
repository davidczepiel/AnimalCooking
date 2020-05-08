#include "Sink.h"
#include "GameConfig.h"

Sink::Sink(Vector2D pos,Transport* p1, Transport* p2, EntityManager* mng) :Entity(SDLGame::instance(),mng), Interactive(p1, p2,nullptr), nTries(), lastTry() {
	sV =addComponent<SinkViewer>(this);
	position_ = pos;
	size_ = Vector2D(128, 128);
	maxTries = SDLGame::instance()->getRandGen()->nextInt(config::SINK_MIN_TRIES, config::SINK_MAX_TRIES);
}

Sink::~Sink() {
}

void Sink::action1(int iDp) {
	if (SDLGame::instance()->getTime() - lastTry < config::SINK_CADENCE) {
		++nTries;
		sV->setOnAction(true);
		lastTry = SDLGame::instance()->getTime();
		//Dependiendo del numero que me llegue me trabajo con el player 1 o 2
		Transport* player;
		if (iDp == 0) player = player1_;
		else player = player2_;

		//Y SI Y SOLO SI tiene un utensilio le digo que se limpie
		if (nTries >= maxTries && player->getObjectTypeInHands() == Resources::PickableType::Utensil) {
			static_cast<Utensil*>(player->getObjectInHands())->cleanUp();
			nTries = 0;
			sV->setOnAction(false);
			maxTries = SDLGame::instance()->getRandGen()->nextInt(config::SINK_MIN_TRIES, config::SINK_MAX_TRIES);
		}	
	}
	else {
		nTries = 0;
		lastTry = SDLGame::instance()->getTime();
		sV->setOnAction(false);
	}
}