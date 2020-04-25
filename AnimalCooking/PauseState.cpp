#include "PauseState.h"
#include "MenuState.h"
#include "PlayState.h"
//#include "ConfigState.h"

PauseState::PauseState(AnimalCooking* ac) : State(ac)
{
	cout << "PauseState";
	int x = SDLGame::instance()->getWindowWidth()/2;
	int y = SDLGame::instance()->getWindowHeight()/5;
	int buttonHeight = 40;
	int buttonWidth = 80;
	resumeButton = stage->addEntity();
	resumeButton->addComponent<Transform>(Vector2D(x-(buttonWidth/2), y-(buttonHeight/2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	resumeButton->addComponent<ButtonBehaviour>(resumeCallback, app);
	resumeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(resumeButton, ecs::GroupID::Layer1);
	configButton = stage->addEntity();
	configButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 2*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	configButton->addComponent<ButtonBehaviour>(configCallback, app);
	configButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(configButton, ecs::GroupID::Layer1);

	menuButton = stage->addEntity();
	menuButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 3*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	menuButton->addComponent<ButtonBehaviour>(menuCallback, app);
	menuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(menuButton, ecs::GroupID::Layer1);

	closeButton = stage->addEntity();
	closeButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 4*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	closeButton->addComponent<ButtonBehaviour>(closeCallback, app);
	closeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(closeButton, ecs::GroupID::Layer1);
}

PauseState::~PauseState()
{
	delete resumeButton;
	delete configButton;
	delete menuButton;

	resumeButton = nullptr;
	configButton = nullptr;
	menuButton = nullptr;
}

void PauseState::menuCallback(AnimalCooking* ac)
{
	cout << "Menu";
	FSM* fsm= SDLGame::instance()->getFSM();
	for (int i = 0; i < 3; i++)
	{
		fsm->popState();
	}
}

void PauseState::configCallback(AnimalCooking* ac)
{
	cout << "Config";
	SDLGame::instance()->getFSM()->pushState(new ConfigState(ac));
}

void PauseState::resumeCallback(AnimalCooking* ac)
{
	cout << "Resume";
	SDLGame::instance()->getFSM()->popState([]() { static_cast<PlayState*>(SDLGame::instance()->getFSM()->currentState())->resumeTimers(); });
}

void PauseState::closeCallback(AnimalCooking* ac)
{
	ac->stop();
}

