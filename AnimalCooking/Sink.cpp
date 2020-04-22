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
	//Me quedo con el player que está interactuando
			Transport* player;
			if (iDp == 0) player = player1_;
			else player = player2_;
			//en caso de que se pueda limpiar y el player tenga un utensilio limpio
		if (SDL_GetTicks()-lastClean >cadence && player->getObjectTypeInHands() == Resources::PickableType::Utensil) {
			lastClean = SDL_GetTicks();
			SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Wash, 0);
			canClean = false;
				static_cast<Utensil*>(player->getObjectInHands())->cleanUp();
		}
}