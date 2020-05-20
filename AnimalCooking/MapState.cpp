#include "MapState.h"
#include "ScreenLoader.h"
#include "SDL_macros.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviour.h"
#include "ButtonPadNavigation.h"
#include "MapLevelPool.h"
#include "MapConfig.h"

MapState::MapState(AnimalCooking* ac) :
	State(ac),
	maxLevels_(0),
	currentLevel_(0),
	lastLevel_(0),
	bgText_(nullptr),
	housesBackgroundText_(nullptr),
	playButtonText_(nullptr),
	returnButtonText_(nullptr),
	playerName_("Player"){

		game_ = SDLGame::instance();
		maxLevels_ = game_->getMaxLevels();
		casillaX = game_->getCasillaX();
		casillaY = game_->getCasillaY();
		
		//Background textures
		bgText_ = game_->getTextureMngr()->getTexture(Resources::MapStateBackground);
		housesBackgroundText_ = game_->getTextureMngr()->getTexture(Resources::MapStateHousesBackground);
		//Play and return buttons textures
		playButtonText_ = game_->getTextureMngr()->getTexture(Resources::MapStatePlayButton);
		returnButtonText_ = game_->getTextureMngr()->getTexture(Resources::MapStateReturnButton);

		//Recogertexturabotones

		//MapPool
		Entity* pool = stage->addEntity();
		pool->addComponent<MapPool>();

		askName();
		init();
}

MapState::~MapState() {
	MapConfig mapCFG(playerName_);
	mapCFG.save();
}

void MapState::init() {
	//mapPool_ = GETCMP1_(MapLevelPool)->getMapPool();

	playButton_ = stage->addEntity();
	returnButton_ = stage->addEntity();
	padNavigation_ = stage->addEntity();

	stage->addToGroup(playButton_, ecs::GroupID::Layer1);
	stage->addToGroup(returnButton_, ecs::GroupID::Layer1);

	//playButton_->addComponent<Transform>(Vector2D(0,0));
	//playButton_->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapStatePlayButton));
	//playButton_->addComponent<ButtonBehaviour>();

	//returnButton_->addComponent<Transform>(Vector2D(0, 0));
	//returnButton_->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapStateReturnButton));
	//returnButton_->addComponent<ButtonBehaviour>();

	
}

void MapState::draw()
{
	bgText_->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
	State::draw();
}

void MapState::update()
{
	State::update();
	if (currentLevel_ != lastLevel_) {
		//currentLevelInfo = levelsInfo[currentLevel_];		
	}
}

void MapState::askName() {
	Entity* nameAsker = stage->addEntity();
	nameAsker->addComponent<NameAsker>();
	stage->addToGroup(nameAsker, ecs::GroupID::topLayer);
}

void MapState::loadGame() {
	MapConfig mapCFG(playerName_);
	vector<levelInfo> levelsInfo_ = mapCFG.getLevelInfoRecipes();


	for (int x = 0; x < levelsInfo_.size(); x++) {
		Entity* level = stage->addEntity();
		level->addComponent<ButtonBehaviour>();
		level->addComponent<ButtonRenderer>();
		level->addComponent<MapLevel>();
		//levelsEntityList_
	}
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

//ButtonPadNavigation* b =padNavigation_->addComponent<ButtonPadNavigation>();
//b->AddButton(screenLoaderButton_,nullptr,backButton_,nullptr,nullptr);
//b->AddButton(backButton_, screenLoaderButton_, nullptr, nullptr, nullptr);
//if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)))
//	GETCMP2(screenLoaderButton_, ButtonBehaviour)->setFocusByController(true);