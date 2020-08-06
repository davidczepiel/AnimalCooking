#include "UtensilsPool.h"

UtensilsPool::UtensilsPool(size_t size) : displayIcons_(false),iconDisplayStart_(0),iconDisplayTime_(2000), Component(ecs::UtensilsPool)
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
		if (GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_LEFTSHOULDER) || GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_LEFTSHOULDER)) {
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


