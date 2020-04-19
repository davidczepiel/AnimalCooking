#include "PauseState.h"
#include "PauseState.h"
#include"MenuState.h"
#include"PlayState.h"
//#include "ConfigState.h"

PauseState::PauseState(AnimalCooking* ac) : State(ac)
{
	cout << "PauseState";

	resumeButton = stage->addEntity();
	resumeButton->addComponent<Transform>(Vector2D(50, 50), Vector2D(0, 0), 80, 40, 0);
	resumeButton->addComponent<ButtonBehaviour>(resumeCallback, app);
	resumeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(resumeButton, ecs::GroupID::Layer1);
	configButton = stage->addEntity();
	configButton->addComponent<Transform>(Vector2D(50, 100), Vector2D(0, 0), 80, 40, 0);
	configButton->addComponent<ButtonBehaviour>(configCallback, app);
	configButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(configButton, ecs::GroupID::Layer1);

	menuButton = stage->addEntity();
	menuButton->addComponent<Transform>(Vector2D(50, 150), Vector2D(0, 0), 80, 40, 0);
	menuButton->addComponent<ButtonBehaviour>(menuCallback, app);
	menuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(menuButton, ecs::GroupID::Layer1);

	closeButton = stage->addEntity();
	closeButton->addComponent<Transform>(Vector2D(50, 200), Vector2D(0, 0), 80, 40, 0);
	closeButton->addComponent<ButtonBehaviour>(menuCallback, app);
	closeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	stage->addToGroup(closeButton, ecs::GroupID::Layer1);
}

PauseState::~PauseState()
{
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
	SDLGame::instance()->getFSM()->popState();
}

void PauseState::closeCallback(AnimalCooking* ac)
{
	ac->stop();
}

