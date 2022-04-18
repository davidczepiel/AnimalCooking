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
#include "IntroState.h"

#include "Tracker.h"
#include "SessionEndEvent.h"
#include "SessionStartEvent.h"


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

	game_ = SDLGame::init("AnimalCooking", 1000, 800);
	GPadController::instance()->getPlayerGPADS();
	//game_->toggleFullScreen();
	//game_->getFSM()->pushState(new PlayState());
	game_->getFSM()->pushState(new IntroState /*EndState*/(this));
	//game_->getFSM()->pushState(new MapState (this));
	game_->getFSM()->refresh();

}

void AnimalCooking::closeGame() {

	Tracker::Instance()->End();
	delete Tracker::Instance();
}

void AnimalCooking::start() {
	exit_ = false;

	Tracker::Init();
	Tracker::Instance()->setGameID(0);
	Tracker::Instance()->Start();

	while (!exit_) {
		Uint32 startTime = game_->getTime();


		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 100.0 / 6.0)
			SDL_Delay(100.0 / 6.0 - frameTime);
	}
}

void AnimalCooking::stop() {
	exit_ = true;
	
}

void AnimalCooking::handleInput() {


	SDL_Event event;
	InputHandler::instance()->clearState();
	GPadController::instance()->setIsAnyButtonJustPressed();
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
			stop();
		else {
			InputHandler::instance()->update(event);
			GPadController::instance()->update(event);
		}
	}
	if (pauseRequest() && dynamic_cast<PlayState*>(game_->getFSM()->currentState()) != nullptr)
	{
		static_cast<PlayState*>(game_->getFSM()->currentState())->pauseTimers();
		game_->getFSM()->pushState(new PauseState(this));
	}
}

bool AnimalCooking::pauseRequest() {
	if (InputHandler::instance()->isKeyDown(SDLK_ESCAPE) || 
		GPadController::instance()->playerPressed(0,SDL_CONTROLLER_BUTTON_START) || GPadController::instance()->playerPressed(1, SDL_CONTROLLER_BUTTON_START) || GPadController::instance()->playerPressed(0, SDL_CONTROLLER_BUTTON_START))
		return true;
	else 
		return false;
}

void AnimalCooking::update() {
	game_->getFSM()->currentState()->update();
	game_->getFSM()->refresh();


}

void AnimalCooking::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00000000));
	SDL_RenderClear(game_->getRenderer());


	game_->getFSM()->currentState()->draw();


	SDL_RenderPresent(game_->getRenderer());
}

