#include "PauseState.h"
#include "PauseState.h"
#include"MenuState.h"
#include"PlayState.h"
//#include "ConfigState.h"

PauseState::PauseState() : State()
{
	cout << "PauseState";

	resumeButton = stage->addEntity();
	resumeButton->addComponent<Transform>(Vector2D(50, 50), Vector2D(0, 0), 80, 40, 0);
	resumeButton->addComponent<ButtonBehaviour>(resumeCallback);
	resumeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));

	configButton = stage->addEntity();
	configButton->addComponent<Transform>(Vector2D(50, 100), Vector2D(0, 0), 80, 40, 0);
	configButton->addComponent<ButtonBehaviour>(configCallback);
	configButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));

	menuButton = stage->addEntity();
	menuButton->addComponent<Transform>(Vector2D(50, 150), Vector2D(0, 0), 80, 40, 0);
	menuButton->addComponent<ButtonBehaviour>(menuCallback);
	menuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
}

PauseState::~PauseState()
{
	resumeButton = nullptr;
	configButton = nullptr;
	menuButton = nullptr;
}

void PauseState::menuCallback()
{
	cout << "Menu";
	//SDLGame::instance()->getFSM()->popState();
	//SDLGame::instance()->getFSM()->popState();
}

void PauseState::configCallback()
{
	cout << "Config";
	//SDLGame::instance()->getFSM()->pushState(new ConfigState());
}

void PauseState::resumeCallback()
{
	cout << "Resume";
	//SDLGame::instance()->getFSM()->popState();
}

