#include "ConfigState.h"

ConfigState::ConfigState() :  State()
{
	cout << "Config State" << endl;
	game_ = SDLGame::instance();

	backButton_ = stage->addEntity();

	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2),Vector2D(),300,100,0);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),nullptr);
}

void ConfigState::backButtonCallback()
{

	SDLGame::instance()->getFSM()->popState();
}
