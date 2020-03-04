#include "MenuState.h"

static void playMenuCallback(SDLGame* game) {
	//game->getFSM()->pushState(/*MapState*/);
	cout << "playMenu" << endl;
}

static void optionsMenuCallback(SDLGame* game) {
	//game->getFSM()->pushState(/*OptionsState*/);
	cout << "options" << endl;
}

static void creditsMenuCallback(SDLGame* game) {
	//game->getFSM()->pushState(/*CreditsState*/);
	cout << "credits" << endl;
}

MenuState::MenuState() : State() {
	cout << "Menu State" << endl;
	game_ = SDLGame::instance();

	playMenuButton_ = stage->addEntity();
	optionsMenu_ = stage->addEntity();
	creditsMenu_ = stage->addEntity();

	playMenuButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
	playMenuButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Test), game_->getTextureMngr()->getTexture(Resources::Test));
	playMenuButton_->addComponent<ButtonBehaviour>(playMenuCallback);

	optionsMenu_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 1), Vector2D(0, 0), 200.0, 100, 0);
	optionsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Test), game_->getTextureMngr()->getTexture(Resources::Test));
	optionsMenu_->addComponent<ButtonBehaviour>(optionsMenuCallback);

	creditsMenu_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 2), Vector2D(0, 0), 200.0, 100, 0);
	creditsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Test), game_->getTextureMngr()->getTexture(Resources::Test));
	creditsMenu_->addComponent<ButtonBehaviour>(creditsMenuCallback);
}


