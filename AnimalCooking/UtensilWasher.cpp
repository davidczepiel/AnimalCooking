#include "UtensilWasher.h"
UtensilWasher::UtensilWasher(SDL_Keycode button, Transport* p1, Transport* p2) : Interactive(p1, p2), Component(ecs::UtensilWasher),
button(button) {
	lastClean = 0;
	cadence = 100;
}

void UtensilWasher::update() {
}
void UtensilWasher::init() {
	text = SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo); //textura de ejemplo
}

void UtensilWasher::draw() {

	//if (dynamic_cast<Utensil*>(player1_->getObjectInHands()) != nullptr) {
	//	int progress = 50 * (1 - (dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() / 100));
	//	cout << dynamic_cast<Utensil*>(player1_->getObjectInHands())->getDirt() << endl;

	//	SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo)->render(RECT(100, 100, progress, 50));
	//}
}


void UtensilWasher::interactive(int iDp) {

	if(SDL_GetTicks())
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