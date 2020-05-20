#include "MapState.h"
#include "ScreenLoader.h"
#include "SDL_macros.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviourNC.h"
#include "MapConfig.h"
#include "ButtonPadNavigation.h"
#include "MapChooser.h"

MapState::MapState(AnimalCooking* ac) :
	State(ac),
	infoBox_(nullptr),
	playButton_(nullptr),
	returnButton_(nullptr),
	levelButtonsPool_(),
	padNavigation_(nullptr),
	bgText_(nullptr),
	housesBackgroundText_(nullptr),
	playButtonText_(nullptr),
	returnButtonText_(nullptr), 
	maxLevels_(0),
	currentLevel_(0),
	lastLevel_(0),
	playerName_("Player") {

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

	chooseOption();
	//init();
	//askName();
}

MapState::~MapState() {

}

void MapState::chooseOption() {
	Entity* chooser = stage->addEntity();
	chooser->addComponent<MapChooser>();
	stage->addToGroup(chooser, ecs::GroupID::topLayer);

	newGameButton_ = stage->addEntity();
	newGameButton_->addComponent<Transform>(
		Vector2D(5 * casillaX, 2.5 * casillaY),
		Vector2D(),
		6 * casillaX,
		1.5 * casillaY,
		0);
	newGameButton_->addComponent<ButtonBehaviour>(newGameCallback, app);
	newGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::MapChooserPannel), game_->getTextureMngr()->getTexture(Resources::MapNewGameButton));
	stage->addToGroup(newGameButton_, ecs::GroupID::topLayer);

	loadGameButton_ = stage->addEntity();
	loadGameButton_->addComponent<Transform>(
		Vector2D(5 * casillaX, 4.5 * casillaY),
		Vector2D(),
		6 * casillaX,
		1.5 * casillaY,
		0);
	loadGameButton_->addComponent<ButtonBehaviour>(loadGameCallback, app);
	loadGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::MapChooserPannel), game_->getTextureMngr()->getTexture(Resources::MapLoadGameButton));
	stage->addToGroup(loadGameButton_, ecs::GroupID::topLayer);
}

void MapState::init() {
	

	
}

void MapState::draw()
{
	bgText_->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
	State::draw();
}

void MapState::update()
{
	for (auto& e : stage->getEntites()) {
		if (!hasToBreak)
			e->update();
		else break;
	}
	hasToBreak = false;
}


void MapState::askName() {
	Entity* nameAsker = stage->addEntity();
	nameAsker->addComponent<NameAsker>();
	stage->addToGroup(nameAsker, ecs::GroupID::topLayer);
}

void MapState::loadGame() {
	hasToBreak = true;
	MapConfig mapCFG(playerName_);
	vector<levelInfo> levelsInfo_ = mapCFG.getLevelInfoRecipes();

	infoBox_ = stage->addEntity();
	playButton_ = stage->addEntity();
	playButton_->addComponent<Transform>(
		Vector2D(3 * casillaX, 1.5 * casillaY),
		Vector2D(),
		3 * casillaX,
		1.5 * casillaY,
		0);

	playButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	playButton_->addComponent<ButtonRenderer>(playButtonText_, nullptr);
	stage->addToGroup(playButton_, ecs::GroupID::topLayer);
	stage->addToGroup(infoBox_, ecs::GroupID::topLayer);
	infoBox_->addComponent<MapInfoBoxViewer>();

	for (int x = 0; x < levelsInfo_.size(); x++) {
		Entity* level = stage->addEntity();
		level->addComponent<ButtonBehaviourNC>(infoBox_, levelsInfo_[x]);
		level->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::MapRestaurantButton), nullptr);
		levelButtonsPool_.push_back(level);
	}
	configPadNavigation();
}

void MapState::saveGame()
{
	MapConfig mapCFG(playerName_);
	mapCFG.save();
}


void MapState::newGameCallback(AnimalCooking* ac)
{
}

void MapState::loadGameCallback(AnimalCooking* ac)
{

}

void MapState::screenLoaderCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->haltMusic();
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	int cl = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState())->getCurrentLevel();
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(cl + 2, ac));
}

void MapState::backButtonCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void MapState::configPadNavigation(){
	Entity* pad = stage->addEntity();
	padNavigation_ = pad->addComponent<ButtonPadNavigation>();

	padNavigation_->AddButton(levelButtonsPool_.at(0), levelButtonsPool_.at(1), nullptr, nullptr, levelButtonsPool_.at(2));
	padNavigation_->AddButton(levelButtonsPool_.at(1), nullptr, levelButtonsPool_.at(0), nullptr, levelButtonsPool_.at(2));
	padNavigation_->AddButton(levelButtonsPool_.at(2), nullptr, nullptr, levelButtonsPool_.at(1), levelButtonsPool_.at(3));
	padNavigation_->AddButton(levelButtonsPool_.at(3), nullptr, nullptr, levelButtonsPool_.at(2), levelButtonsPool_.at(4));
	padNavigation_->AddButton(levelButtonsPool_.at(4), nullptr, nullptr, levelButtonsPool_.at(2), nullptr);
}
