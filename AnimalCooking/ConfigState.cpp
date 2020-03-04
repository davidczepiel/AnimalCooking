#include "ConfigState.h"

ConfigState::ConfigState() :  State()
{
	cout << "Config State" << endl;
	game_ = SDLGame::instance();

	backButton_ = stage->addEntity();

	backButton_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback);
	backButton_->addComponent<ButtonRenderer>();
}

void ConfigState::backButtonCallback(SDLGame* game)
{
	//Que vuelva a fromState_

	game->getFSM()->popState();
}
