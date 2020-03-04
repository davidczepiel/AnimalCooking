#include "MenuState.h"

static void playMenuCallback(SDLGame* game) {
	//Abrir estado juego
}

static void optionsMenuCallback(SDLGame* game) {
	//Abrir estado opciones
}

static void creditsMenuCallback(SDLGame* game) {
	//Abrir estado opciones
}

MenuState::MenuState() : State() {
	cout << "Menu State" << endl;
	game_ = SDLGame::instance();

	playMenuButton_ = stage->addEntity();
	optionsMenu_ = stage->addEntity();
	creditsMenu_ = stage->addEntity();

	playMenuButton_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth()/2, game_->getWindowHeight() / 4));
	playMenuButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Airplanes), game_->getTextureMngr()->getTexture(Resources::HelloWorld));
	playMenuButton_->addComponent<ButtonBehaviour>(playMenuCallback);

	optionsMenu_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 3));
	optionsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Airplanes), game_->getTextureMngr()->getTexture(Resources::HelloWorld));
	optionsMenu_->addComponent<ButtonBehaviour>(playMenuCallback);

	creditsMenu_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	creditsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Airplanes), game_->getTextureMngr()->getTexture(Resources::HelloWorld));
	creditsMenu_->addComponent<ButtonBehaviour>(creditsMenuCallback);
}


