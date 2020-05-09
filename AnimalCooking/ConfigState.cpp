#include "ConfigState.h"

ConfigState::ConfigState(AnimalCooking* ac) :  State(ac)
{
	cout << "Config State" << endl;
	game_ = SDLGame::instance();

	backButton_ = stage->addEntity();

	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2),Vector2D(),300,100,0);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),nullptr);
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}
