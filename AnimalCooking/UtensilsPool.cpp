#include "UtensilsPool.h"

UtensilsPool::UtensilsPool(size_t size) : displayIcons_(false),iconDisplayStart_(0),iconDisplayTime_(2000), Component(ecs::UtensilsPool),
keys1(SDLGame::instance()->getOptions().players_keyboardKeys[0]),keys2(SDLGame::instance()->getOptions().players_keyboardKeys[1]),
buttons1(SDLGame::instance()->getOptions().players_gPadButtons[0]),buttons2(SDLGame::instance()->getOptions().players_gPadButtons[1])
{
    pool_.reserve(size);
}

UtensilsPool::~UtensilsPool() {
	for (Utensil* u : pool_) {
		delete u;
	}
}

void UtensilsPool::SetGameLogic(GameLogic* gl)
{
	for (int i = 0; i < pool_.size(); i++) {
		if (pool_.at(i) != nullptr) {
			pool_.at(i)->setGameLogic(gl);
		}
	}

}

void UtensilsPool::update()
{
	if (!displayIcons_) {
		InputHandler* keyboard = InputHandler::instance();

		if (GPadController::instance()->playerPressed(0, buttons1.INFOUTENSILS) || GPadController::instance()->playerPressed(1, buttons2.INFOUTENSILS) ||
			keyboard->isKeyDown(keys1.INFOUTENSILS) || keyboard->isKeyDown(keys2.INFOUTENSILS)) {
			iconDisplayStart_ = SDL_GetTicks();
			changeDisplay(true);
		}
	}
	else {
		if (SDL_GetTicks() - iconDisplayStart_ > iconDisplayTime_) {
			changeDisplay(false);
		}
	}
}

void UtensilsPool::changeDisplay(bool b)
{
	displayIcons_ = b;
	for (int i = 0; i < pool_.size(); i++) {
		if (pool_.at(i) != nullptr) {
			pool_.at(i)->setDisplayIcon(b);
		}
	}
}


