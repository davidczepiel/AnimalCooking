#include "Sink.h"
Sink::Sink(Vector2D pos,Transport* p1, Transport* p2, EntityManager* mng) :Entity(SDLGame::instance(),mng), Interactive(p1, p2,nullptr),cadence(500),canClean(true){
	addComponent<SinkViewer>(this);
	position_ = pos;
	lastClean = SDL_GetTicks();
	size_ = Vector2D(128, 128);
}

Sink::~Sink() {

}


void Sink::action1(int iDp) {
		if (SDL_GetTicks()-lastClean >cadence) {
			lastClean = SDL_GetTicks();
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Wash, 0);
			canClean = false;
			//Dependiendo del numero que me llegue me trabajo con el player 1 o 2
			Transport* player;
			if (iDp == 0) player = player1_;
			else player = player2_;
			//Y SI Y SOLO SI tiene un utensilio le digo que se limpie
			if (player->getObjectTypeInHands() == Resources::PickableType::Utensil)
				static_cast<Utensil*>(player->getObjectInHands())->cleanUp();
		}
}