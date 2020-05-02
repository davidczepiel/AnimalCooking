#include "EndState.h"
EndState::EndState(AnimalCooking* ac) :State(ac) {

	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::End_Win, 0);

	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 - 150,
		SDLGame::instance()->getWindowHeight() / 2 - 125), Vector2D(), 300, 100, 0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);

	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	Entity* returnToLevelButton = stage->addEntity();
	stage->addToGroup(returnToLevelButton, ecs::GroupID::Layer1);
	returnToLevelButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 -150,
		SDLGame::instance()->getWindowHeight() / 2 ), Vector2D(), 300, 100, 0);
	returnToLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
	returnToLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	Entity* returnToMenuButton = stage->addEntity();
	stage->addToGroup(returnToMenuButton, ecs::GroupID::Layer1);

	returnToMenuButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() / 2 - 150,
		SDLGame::instance()->getWindowHeight() / 2 +150), Vector2D(), 300, 100, 0);
	returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);
	returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);

}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(Resources::Nivel1,ac));
}
void EndState::goToMapState(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	FSM* fsm = SDLGame::instance()->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}

}
void EndState::goToMenuState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->popState();
	SDLGame::instance()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);

}