#include "MenuState.h"

MenuState::MenuState() : State() {
	cout << "Menu State" << endl;
	game_ = SDLGame::instance();

	playMenuButton_ = stage->addEntity();
	optionsMenu_ = stage->addEntity();

	playMenuButton_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth()/2, game_->getWindowHeight() / 4));
	playMenuButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Airplanes), game_->getTextureMngr()->getTexture(Resources::HelloWorld));
	playMenuButton_->addComponent<ButtonBehaviour>(playMenuCallback);

	optionsMenu_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2));
	optionsMenu_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Airplanes), game_->getTextureMngr()->getTexture(Resources::HelloWorld));
	optionsMenu_->addComponent<ButtonBehaviour>(playMenuCallback);
}

void MenuState::playMenuCallback(SDLGame* game) {
	//Abrir playState
}

void MenuState::optionsMenuCallback(SDLGame* game) {
	//Abrir menu opciones
}
void MenuState::creditsMenuCallback(SDLGame* game) {
	//Abrir menu opciones
}

