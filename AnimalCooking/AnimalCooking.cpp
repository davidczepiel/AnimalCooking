#include "SDL_macros.h"
#include "AnimalCooking.h"
#include <assert.h>

#include "InputHandler.h"

#include "Transform.h"
#include "SDLGame.h"
#include "MenuState.h"
#include "LoadState.h"
#include "SDL_macros.h"

using namespace std;

AnimalCooking::AnimalCooking() :
		game_(nullptr), //
		fsm_(nullptr), //
		exit_(false) {
	initGame();
}

AnimalCooking::~AnimalCooking() {
	closeGame();
}

void AnimalCooking::initGame() {

	game_ = SDLGame::init("AnimalCooking", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	fsm_ = new FSM(game_);
	fsm_->PushState(new MenuState());
	
}

void AnimalCooking::closeGame() {
	delete fsm_;
}

void AnimalCooking::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void AnimalCooking::stop() {
	exit_ = true;
}

void AnimalCooking::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
			}
		}
		if (ih->isKeyDown(SDLK_p))
			fsm_->PushState(new MenuState());
		else if (ih->isKeyDown(SDLK_m))
			fsm_->PushState(new LoadState());
		else if(ih->isKeyDown(SDLK_o)) fsm_->PopState();
	}

}

void AnimalCooking::update() {
	fsm_->CurrentState()->Update();
}

void AnimalCooking::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	fsm_->CurrentState()->Draw();

	SDL_RenderPresent(game_->getRenderer());
}

