#include "EndState.h"
EndState::EndState() :State() {
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 - 150,
		SDLGame::instance()->getWindowHeight() / 2 - 125), Vector2D(), 300, 100, 0);
	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton1), nullptr);
	Entity* returnToLevelButton = stage->addEntity();
	returnToLevelButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 -150,
		SDLGame::instance()->getWindowHeight() / 2 ), Vector2D(), 300, 100, 0);
	returnToLevelButton->addComponent<ButtonBehaviour>(goToLoadState);
	returnToLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton2), nullptr);
}
void EndState::goToLoadState() {
	cout << "vamos p'a la partida";
	/*Nosequé->fsm()->cambiaestado()*/
}
void EndState::goToMapState() {
	cout << "vamos p'al mapa";
	/*Nosequé->fsm()->cambiaestado()*/
}