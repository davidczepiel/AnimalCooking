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

MapState::MapState(AnimalCooking* ac): State(ac), unlockedLevels(0), maxLevels(0) {
	game_ = SDLGame::instance();
	unlockedLevels = game_->getCurrenUnlockLevel();
	maxLevels = game_->getMaxLevels();
	cout << "Map State" << endl;

	Entity* screenLoaderButton_ = stage->addEntity();
	Entity* backButton_ = stage->addEntity();
	Entity* padNavigation_ = stage->addEntity();
	stage->addToGroup(screenLoaderButton_, ecs::GroupID::Layer1);
	stage->addToGroup(backButton_, ecs::GroupID::Layer1);
	stage->addToGroup(padNavigation_, ecs::GroupID::Layer1);

	screenLoaderButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
	jugarText = new Texture(game_->getRenderer(), "Play", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)),{ COLOR(0x000000ff) });
	
	ButtonBehaviour* bb = screenLoaderButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	ButtonRenderer* br = screenLoaderButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), jugarText);
	bb->setButtonRenderer(br);

	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 1), Vector2D(0, 0), 200.0, 100, 0);
	volverText = new Texture(game_->getRenderer(), "Return", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
	bb = backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	br = backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), volverText);
	bb->setButtonRenderer(br);

	ButtonPadNavigation* b =padNavigation_->addComponent<ButtonPadNavigation>();
	b->AddButton(screenLoaderButton_,nullptr,backButton_,nullptr,nullptr);
	b->AddButton(backButton_, screenLoaderButton_, nullptr, nullptr, nullptr);
	if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)))
		GETCMP2(screenLoaderButton_, ButtonBehaviour)->setFocusByController(true);
}