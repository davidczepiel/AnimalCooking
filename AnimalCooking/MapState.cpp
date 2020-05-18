#include "MapState.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviour.h"
#include "ButtonPadNavigation.h"

MapState::MapState(AnimalCooking* ac) :
	State(ac),
	unlockedLevels(0),
	maxLevels(0),
	backgroundTexture(nullptr),
	housesBackgroundTexture(nullptr),
	houseButtonTexture(nullptr),
	houseButtonOverTexture(nullptr),
	playButtonTexture(nullptr),
	returnButtonTexture(nullptr),
	infoBoxTexture(nullptr),
	levelsInfo() {

		game_ = SDLGame::instance();
		unlockedLevels = game_->getCurrenUnlockLevel();
		maxLevels = game_->getMaxLevels();
		
		backgroundTexture = game_->getTextureMngr()->getTexture(Resources::MapStateBackground);
		housesBackgroundTexture = game_->getTextureMngr()->getTexture(Resources::MapStateHousesBackground);
		houseButtonTexture = game_->getTextureMngr()->getTexture(Resources::MapStateHouseButton);
		houseButtonOverTexture = game_->getTextureMngr()->getTexture(Resources::MapStateHouseButtonOver);
		infoBoxTexture = game_->getTextureMngr()->getTexture(Resources::MapStateInfoBox);
		playButtonTexture = game_->getTextureMngr()->getTexture(Resources::MapStatePlayButton);
		returnButtonTexture = game_->getTextureMngr()->getTexture(Resources::MapStateReturnButton);

		//Mapconfig
		MapConfig mapCFG;




		//OldButtons
		Entity* screenLoaderButton_ = stage->addEntity();
		Entity* backButton_ = stage->addEntity();
		Entity* padNavigation_ = stage->addEntity();
		stage->addToGroup(screenLoaderButton_, ecs::GroupID::Layer1);
		stage->addToGroup(backButton_, ecs::GroupID::Layer1);
		stage->addToGroup(padNavigation_, ecs::GroupID::Layer1);

		screenLoaderButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
		playButtonTexture = new Texture(game_->getRenderer(), "Play", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)),{ COLOR(0x000000ff) });
	
		ButtonBehaviour* bb = screenLoaderButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
		ButtonRenderer* br = screenLoaderButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), playButtonTexture);
		bb->setButtonRenderer(br);

		backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 1), Vector2D(0, 0), 200.0, 100, 0);
		returnButtonTexture = new Texture(game_->getRenderer(), "Return", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
		bb = backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
		br = backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), returnButtonTexture);
		bb->setButtonRenderer(br);

		ButtonPadNavigation* b =padNavigation_->addComponent<ButtonPadNavigation>();
		b->AddButton(screenLoaderButton_,nullptr,backButton_,nullptr,nullptr);
		b->AddButton(backButton_, screenLoaderButton_, nullptr, nullptr, nullptr);
		if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)))
			GETCMP2(screenLoaderButton_, ButtonBehaviour)->setFocusByController(true);
}

void MapState::draw()
{
	backgroundTexture->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
}

void MapState::update()
{

}







void MapState::screenLoaderCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->haltMusic();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(Resources::Level::Nivel1, ac));
}

void MapState::backButtonCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}