#include "Sink.h"
Sink::Sink(Vector2D pos,Transport* p1, Transport* p2, EntityManager* mng) :Entity(SDLGame::instance(),mng), Interactive(p1, p2,nullptr),cadence(1),canClean(true){
	addComponent<SinkViewer>(this);
	position_ = pos;
	cleanTimer = new Timer();
	cleanTimer->setTime(cadence);
	size_ = Vector2D(128, 128);
}

Sink::~Sink() {
	delete cleanTimer;
	cleanTimer = nullptr;
}

void Sink::update() {
	if (!canClean) {
		cleanTimer->update();
		if (cleanTimer->isTimerEnd()) {
			canClean = true;
			cleanTimer->timerReset();
		}
	}
}


void Sink::draw() { //¿ Para dibujar la barra que indica la cantidad de suciedad que nos queda?

	//if (dynamic_cast<Utensil*>(player1_->getObjectInHands()) != nullptr) {
	//	int progress = 50 * (1 - (dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() / 100));
	//	cout << dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() << endl;

	//	SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo)->render(RECT(100, 100, progress, 50));
	//}
}


void Sink::action1(int iDp) {

		if (canClean) {
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Wash, 0);
			canClean = false;
			cleanTimer->timerStart();
			//Dependiendo del numero que me llegue me trabajo con el player 1 o 2
			Transport* player;
			if (iDp == 0) player = player1_;
			else player = player2_;
			//Y SI Y SOLO SI tiene un utensilio le digo que se limpie
			if (player->getObjectTypeInHands() == Resources::PickableType::Utensil)
				static_cast<Utensil*>(player->getObjectInHands())->cleanUp();

		}
}