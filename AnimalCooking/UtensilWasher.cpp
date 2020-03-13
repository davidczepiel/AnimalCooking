#include "UtensilWasher.h"
UtensilWasher::UtensilWasher(SDL_Keycode button) :

	Component(ecs::UtensilWasher), toBeWashedUtensil(nullptr), button(button) {

	lastClean = 0;
	cadence = 100;


}
void UtensilWasher::update() {
	//si hay que limpiar generamos un n�mero en el intervalo [0,4] que representar� el bot�n a pulsar.
	//como en el vector est�n primero las teclas y luego los botones correspondientes del mando,
	//cada tecla est� separada 4 posiciones de su bot�n correspondiente, as� que para limpiar el 
	//utensilio basta con comprobar que se est� pulsando la tecla o el bot�n

	if (toBeWashedUtensil != nullptr && SDL_GetTicks() - lastClean > cadence) {
		lastClean = SDL_GetTicks();
		InputHandler* ih = SDLGame::instance()->getInputHandler();
		GPadController* gpad = GPadController::instance();
		//aqu� habr�a que preguntar al playerController su ID, pero de momento no se me ocurre c�mo
		if (ih->isKeyDown(button) || gpad->getButtonState(0, SDL_CONTROLLER_BUTTON_A))
		{
			toBeWashedUtensil->cleanUp();
			if (toBeWashedUtensil->getDirt() <= 0)
				toBeWashedUtensil = nullptr;
		}
	}
}
void UtensilWasher::draw() {
	if (toBeWashedUtensil != nullptr) {
		int progress = 50 * (1- toBeWashedUtensil->getDirt() / 100);
		cout << toBeWashedUtensil<<endl;
		cout << toBeWashedUtensil->getDirt()<<endl;

		SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cuchillo)->render(RECT(100, 100, progress, 50));
	}
}