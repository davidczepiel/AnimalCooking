#include "MenuState.h"

 void MenuState::playMenuCallback(AnimalCooking* ac) {
	 SDLGame::instance()->getFSM()->pushState(new MapState(ac));
}

void MenuState::optionsMenuCallback(AnimalCooking* ac) {
	SDLGame::instance() ->getFSM()->pushState(new ConfigState(ac));
}

void MenuState::creditsMenuCallback(AnimalCooking* ac) {
	SDLGame::instance()->getFSM()->pushState(new CreditsState(ac));
}

void MenuState::closeGame(AnimalCooking* ac)
{
	ac->stop();
}

MenuState::MenuState(AnimalCooking* ac) : State(ac) {
	cout << "Menu State" << endl;
	game_ = SDLGame::instance();

	playMenuButton_ = stage->addEntity();
	optionsMenu_ = stage->addEntity();
	creditsMenu_ = stage->addEntity();
	exitButton_ = stage->addEntity();
	stage->addToGroup(playMenuButton_, ecs::GroupID::Layer1);
	stage->addToGroup(optionsMenu_, ecs::GroupID::Layer1);
	stage->addToGroup(creditsMenu_, ecs::GroupID::Layer1);
	stage->addToGroup(exitButton_, ecs::GroupID::Layer1);

	playMenuButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 4) * 0), Vector2D(0, 0), 200.0, 100, 0);
	playMenuButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	playMenuButton_->addComponent<ButtonBehaviour>(playMenuCallback,app);

	optionsMenu_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 4) * 1), Vector2D(0, 0), 200.0, 100, 0);
	optionsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	optionsMenu_->addComponent<ButtonBehaviour>(optionsMenuCallback, app);

	creditsMenu_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 4) * 2), Vector2D(0, 0), 200.0, 100, 0);
	creditsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	creditsMenu_->addComponent<ButtonBehaviour>(creditsMenuCallback, app);

	exitButtonTr_ = exitButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 4) * 3), Vector2D(0, 0), 200.0, 100, 0);
	exitButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	exitButton_->addComponent<ButtonBehaviour>(closeGame, app);
}
