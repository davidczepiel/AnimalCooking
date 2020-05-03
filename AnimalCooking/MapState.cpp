#include "MapState.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviour.h"
#include "ButtonPadNavigation.h"

 void MapState::screenLoaderCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->haltMusic();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(Resources::Level::Nivel1,ac));
}
void MapState::backButtonCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}
MapState::MapState(AnimalCooking* ac): State(ac) {
	game_ = SDLGame::instance();
	cout << "Map State" << endl;

	Entity* screenLoaderButton_ = stage->addEntity();
	Entity* backButton_ = stage->addEntity();
	Entity* padNavigation_ = stage->addEntity();
	stage->addToGroup(screenLoaderButton_, ecs::GroupID::Layer1);
	stage->addToGroup(backButton_, ecs::GroupID::Layer1);
	stage->addToGroup(padNavigation_, ecs::GroupID::Layer1);

	screenLoaderButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
	screenLoaderButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	screenLoaderButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);

	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 1), Vector2D(0, 0), 200.0, 100, 0);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);

	ButtonPadNavigation* b =padNavigation_->addComponent<ButtonPadNavigation>();
	b->AddButton(screenLoaderButton_,nullptr,backButton_,nullptr,nullptr);
	b->AddButton(backButton_, screenLoaderButton_, nullptr, nullptr, nullptr);
}