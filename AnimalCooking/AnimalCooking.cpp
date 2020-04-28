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
#include "PauseState.h"


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
	GPadController::playerDPAD(0);
	GPadController::playerDPAD(1);
	//game_->toggleFullScreen();
	//game_->getFSM()->pushState(new PlayState());
	game_->getFSM()->pushState(new MenuState(this));
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
	InputHandler::instance()->clearState();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			stop();
		else
			InputHandler::instance()->update(event);
	}

	if (pauseRequest()&& dynamic_cast<PlayState*>(game_->getFSM()->currentState())!=nullptr)
		game_->getFSM()->pushState(new PauseState(this));
}

bool AnimalCooking::pauseRequest() {
	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE) || 
		GPadController::playerPressed(0,SDL_CONTROLLER_BUTTON_START) || GPadController::playerPressed(1, SDL_CONTROLLER_BUTTON_START))
		return true;
	else 
		return false;
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

