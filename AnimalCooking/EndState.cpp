#include "EndState.h"
EndState::EndState() :State() {
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 - 150,
		SDLGame::instance()->getWindowHeight() / 2 - 125), Vector2D(), 300, 100, 0);
	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	Entity* returnToLevelButton = stage->addEntity();
	returnToLevelButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 -150,
		SDLGame::instance()->getWindowHeight() / 2 ), Vector2D(), 300, 100, 0);
	returnToLevelButton->addComponent<ButtonBehaviour>(goToLoadState);
	returnToLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	Entity* returnToMenuButton = stage->addEntity();
	returnToMenuButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 - 150,
		SDLGame::instance()->getWindowHeight() / 2 +150), Vector2D(), 300, 100, 0);
	returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState);
	returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);

}
void EndState::goToLoadState() {
	goToMapState();
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(Resources::Nivel1));
}
void EndState::goToMapState() {
	FSM* fsm = SDLGame::instance()->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}

}
void EndState::goToMenuState() {
	goToMapState();
	SDLGame::instance()->getFSM()->popState();
}