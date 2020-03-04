#include "CreditsState.h"




CreditsState::CreditsState() {

	Entity* returnToMenuState = stage->addEntity();
	returnToMenuState->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2, SDLGame::instance()->getWindowHeight()/ 4),Vector2D(0,0),100,50,0);
	returnToMenuState->addComponent<ButtonBehaviour>(GoBackMenu);
	returnToMenuState->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton));
	//Se pondrían los 

	Entity* nombre = stage->addEntity();
	nombre->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth()/2, SDLGame::instance()->getWindowHeight()*3/4),Vector2D(0,-10),300,100,0);
	nombre->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton), SDLGame::instance()->getTextureMngr()->getTexture(Resources::Boton));
}


void CreditsState::GoBackMenu(SDLGame* g) {
	cout << "Hola";
	g->getFSM()->popState();
	cout << "Hola";

}