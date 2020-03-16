#include "Sink.h"
Sink::Sink(Transport* p1, Transport* p2) : Interactive(p1, p2){
	lastClean = 0;
	cadence = 100;
	addComponent<SinkViewer>(this);
}

void Sink::draw() { //¿ Para dibujar la barra que indica la cantidad de suciedad que nos queda?

	//if (dynamic_cast<Utensil*>(player1_->getObjectInHands()) != nullptr) {
	//	int progress = 50 * (1 - (dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() / 100));
	//	cout << dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() << endl;

	//	SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo)->render(RECT(100, 100, progress, 50));
	//}
}


void Sink::interactive(int iDp) {

	if (SDL_GetTicks())
		if (SDL_GetTicks() - lastClean > cadence) {
			lastClean = SDL_GetTicks();
			if (iDp == 0) {
				Utensil* u = dynamic_cast<Utensil*>(player1_->getObjectInHands());
				if (u != nullptr)
					u->cleanUp();
			}
			else {
				Utensil* u = dynamic_cast<Utensil*>(player2_->getObjectInHands());
				if (u != nullptr)
					u->cleanUp();
			}
		}
}