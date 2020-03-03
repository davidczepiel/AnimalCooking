#include "EndState.h"
EndState::EndState() :State() {
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(100,100), Vector2D(), 100, 100, 0);
	returnToMapButton->addComponent<ButtonBehaviour>([](SDLGame* game) {cout << "vamos p'al mapa";/*Nosequé->fsm()->cambiaestado()*/});
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton1),nullptr);
	Entity* returnToLevelButton = stage->addEntity();
	returnToLevelButton->addComponent<Transform>(Vector2D(100, 200), Vector2D(), 100, 100, 0);
	returnToLevelButton->addComponent<ButtonBehaviour>([](SDLGame* game) {cout << "vamos p'a la partida";/*Nosequé->fsm()->cambiaestado()*/});
	returnToLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton2),nullptr);
}