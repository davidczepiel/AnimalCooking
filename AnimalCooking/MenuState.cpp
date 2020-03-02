#include "MenuState.h"

MenuState::MenuState() : State() {
	cout << "Menu State" << endl;
	game_ = SDLGame::instance();

	playMenuButton_ = stage->addEntity();
	optionsMenu_ = stage->addEntity();

	playMenuButton_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth/2, game_->getWindowHeight / 4));
	playMenuButton_->addComponent<ButtonRenderer>();
	playMenuButton_->addComponent<ButtonBehaviour>(playMenuCallback);

	optionsMenu_->addComponent<Transform>()->setPos(Vector2D(game_->getWindowWidth / 2, game_->getWindowHeight / 2));
	optionsMenu_->addComponent<ButtonRenderer>();
	optionsMenu_->addComponent<ButtonBehaviour>(playMenuCallback);
}

void MenuState::playMenuCallback() {

}

void MenuState::optionsMenuCallback() {

}
