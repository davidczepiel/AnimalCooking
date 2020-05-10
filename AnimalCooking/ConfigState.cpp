#include "ConfigState.h"
#include "SDL_macros.h"
#include "MenuState.h"
#include "SDL.h"

ConfigState::ConfigState(AnimalCooking* ac) :  State(ac)
{
	cout << "Config State" << endl;
	game_ = SDLGame::instance();

	backButton_ = stage->addEntity();
	stage->addToGroup(backButton_, ecs::GroupID::ui);
	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10,0);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), 
											  game_->getTextureMngr()->getTexture(Resources::Button));

	Entity* resButton2 = stage->addEntity();
	stage->addToGroup(resButton2, ecs::GroupID::ui);
	resButton2->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, 
		4 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	resButton2->addComponent<ButtonBehaviour>(resButtonCallback, app);
	resButton2->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void ConfigState::resButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->toggleFullScreen();
}