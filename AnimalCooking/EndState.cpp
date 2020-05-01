#include "EndState.h"
EndState::EndState(AnimalCooking* ac) :State(ac) {
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(138,
		SDLGame::instance()->getWindowHeight() - 128), Vector2D(), 64, 64, 0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);

	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapIcon), nullptr);
	Entity* NextLevelButton = stage->addEntity();
	stage->addToGroup(NextLevelButton, ecs::GroupID::Layer1);
	NextLevelButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() - 128,
		SDLGame::instance()->getWindowHeight() - 128), Vector2D(), 64, 64, 45);
	NextLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
	NextLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::NextLevelIcon), nullptr);

	Entity* ResetLevelButton = stage->addEntity();
	stage->addToGroup(ResetLevelButton, ecs::GroupID::Layer1);
	ResetLevelButton->addComponent<Transform>(Vector2D(SDLGame::instance()->getWindowWidth() - 202,
		SDLGame::instance()->getWindowHeight() - 202), Vector2D(), 64, 64, 45);
	ResetLevelButton->addComponent<ButtonBehaviour>(resetLevel, app);
	ResetLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ReplayIcon), nullptr);


	Entity* returnToMenuButton = stage->addEntity();
	stage->addToGroup(returnToMenuButton, ecs::GroupID::Layer1);

	returnToMenuButton->addComponent<Transform>(Vector2D(64,

		SDLGame::instance()->getWindowHeight() - 128), Vector2D(), 64, 64, 0);
	returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);

	returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIcon), nullptr);

}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 1), ac));
}
void EndState::goToMapState(AnimalCooking* ac) {
	FSM* fsm = SDLGame::instance()->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}

}
void EndState::goToMenuState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->popState();
}

void EndState::resetLevel(AnimalCooking* ac)
{
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(SDLGame::instance()->getCurrentLevel(), ac));

}
