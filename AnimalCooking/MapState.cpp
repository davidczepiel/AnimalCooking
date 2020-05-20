#include "MapState.h"
#include "ScreenLoader.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviour.h"
#include "ButtonPadNavigation.h"

MapState::MapState(AnimalCooking* ac) :
	State(ac),
	maxLevels_(0),
	currentLevel_(0),
	lastLevel_(0),
	bgText_(nullptr),
	housesBackgroundText_(nullptr),
	playButtonText_(nullptr),
	returnButtonText_(nullptr),
	levelsInfo_(),
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

		askName();
		init();
}

MapState::~MapState() {
	/*MapConfig mapCFG(playerName);
	mapCFG.save();*/
}

void MapState::init() {
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

	for (int x = 0; x < levelsInfo_.size(); x++) {
		//Entity* level 
		//levelsEntityList_
	}	
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
	//A�adir entidades para introducir nombre
	Entity* inputButton = stage->addEntity();
	inputButton->addComponent<Transform>(
		Vector2D(3 * casillaX, 5 * casillaY),
		Vector2D(),
		2 * casillaX,
		casillaY,
		0
		);
	//inputButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	//inputButton->addComponent<ButtonBehaviour>(, app);
	Entity* nameAsker = stage->addEntity();
	nameAsker->addComponent<NameAsker>();
	stage->addToGroup(nameAsker, ecs::GroupID::topLayer);

}

void MapState::loadGame() {

	//Esto al final cuando ya se tenga el nombre del jugador -> test
	//Mapconfig
	MapConfig mapCFG("test");
	levelsInfo_ = mapCFG.getLevelInfoRecipes();

	//Borrado de entidades
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


////OldButtons
//Entity* screenLoaderButton_ = stage->addEntity();
//Entity* backButton_ = stage->addEntity();
//Entity* padNavigation_ = stage->addEntity();
//stage->addToGroup(screenLoaderButton_, ecs::GroupID::Layer1);
//stage->addToGroup(backButton_, ecs::GroupID::Layer1);
//stage->addToGroup(padNavigation_, ecs::GroupID::Layer1);

//screenLoaderButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 0), Vector2D(0, 0), 200.0, 100, 0);
//playButtonTexture = new Texture(game_->getRenderer(), "Play", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)),{ COLOR(0x000000ff) });

//ButtonBehaviour* bb = screenLoaderButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
//ButtonRenderer* br = screenLoaderButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), playButtonTexture);
//bb->setButtonRenderer(br);

//backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 3) * 1), Vector2D(0, 0), 200.0, 100, 0);
//returnButtonTexture = new Texture(game_->getRenderer(), "Return", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
//bb = backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
//br = backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), returnButtonTexture);
//bb->setButtonRenderer(br);

//ButtonPadNavigation* b =padNavigation_->addComponent<ButtonPadNavigation>();
//b->AddButton(screenLoaderButton_,nullptr,backButton_,nullptr,nullptr);
//b->AddButton(backButton_, screenLoaderButton_, nullptr, nullptr, nullptr);
//if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)))
//	GETCMP2(screenLoaderButton_, ButtonBehaviour)->setFocusByController(true);