#include "MenuState.h"

MenuState::MenuState() : State() {
	cout << "Menu State" << endl;
	playMenuButton = stage->addEntity();
	optionsMenu = stage->addEntity();

	playMenuButton->addComponent<Transform>()->setPos(Vector2D(10, 10));	//cambiar valores
	playMenuButton->addComponent<ButtonRenderer>();
	playMenuButton->addComponent<ButtonBehaviour>();

	optionsMenu->addComponent<Transform>()->setPos(Vector2D(10, 40));		//cambiar valores
	optionsMenu->addComponent<ButtonRenderer>();
	optionsMenu->addComponent<ButtonBehaviour>();
}
