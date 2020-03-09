#include "SDL_macros.h"
#include "AnimalCooking.h"
#include <assert.h>

#include "InputHandler.h"

#include "Transform.h"
#include "CreditsState.h"
#include "SDLGame.h"
#include "PlayState.h"
#include "SDL_macros.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "GPadController.h"


using namespace std;

AnimalCooking::AnimalCooking() :
		game_(nullptr), //
		exit_(false) {
	initGame();
	
}

AnimalCooking::~AnimalCooking() {
	closeGame();
}

void AnimalCooking::initGame() {

	game_ = SDLGame::init("AnimalCooking", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	//game_->getFSM()->pushState(new PlayState());
	game_->getFSM()->pushState(new MenuState());
	game_->getFSM()->refresh();




}

void AnimalCooking::closeGame() {

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


	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		GPadController::instance()->update(event);
		InputHandler::instance()->update(event);
	}
}

void AnimalCooking::update() {
	game_->getFSM()->currentState()->update();
	game_->getFSM()->refresh();

	
}

void AnimalCooking::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());


	game_->getFSM()->currentState()->draw();


	SDL_RenderPresent(game_->getRenderer());
}

