#include "ConfigState.h"
#include "SDL_macros.h"
#include "MenuState.h"

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

	Entity* resButton = stage->addEntity();
	stage->addToGroup(resButton, ecs::GroupID::ui);
	resButton->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, 2 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	resButton->addComponent<ButtonBehaviour>(resButtonCallback, app);
	resButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));

	Entity* resButton3 = stage->addEntity();
	stage->addToGroup(resButton3, ecs::GroupID::ui);
	resButton3->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10,
		3 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	resButton3->addComponent<ButtonBehaviour>(resButtonCallback3, app);
	resButton3->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));

	Entity* resButton2 = stage->addEntity();
	stage->addToGroup(resButton2, ecs::GroupID::ui);
	resButton2->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, 
		4 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	resButton2->addComponent<ButtonBehaviour>(resButtonCallback2, app);
	resButton2->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getFSM()->popState();
	if(SDLGame::instance()->getFSM()->getStackSize() < 3)
		SDLGame::instance()->getFSM()->changeState(new MenuState(ac));
}

void ConfigState::resButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->changeWindowSize(1000, 800);
	SDLGame::instance()->getFSM()->changeState(new ConfigState(ac));
}

void ConfigState::resButtonCallback2(AnimalCooking* ac)
{
	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	SDLGame::instance()->changeWindowSize(DM.w, DM.h);
	SDLGame::instance()->getFSM()->changeState(new ConfigState(ac));
}

void ConfigState::resButtonCallback3(AnimalCooking* ac)
{
	SDLGame::instance()->changeWindowSize(1200, 800);
	SDLGame::instance()->getFSM()->changeState(new ConfigState(ac));
}
