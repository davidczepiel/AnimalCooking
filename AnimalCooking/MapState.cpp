#include "MapState.h"
#include "ScreenLoader.h"
#include "SDL_macros.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviourNC.h"
#include "MapConfig.h"
#include "ButtonPadNavigation.h"

Entity* infoBox_;
Entity* playButton_;
Entity* returnButton_;
vector <Entity*> mapButtonsPool_;
ButtonPadNavigation* padNavigation_;



MapState::MapState(AnimalCooking* ac) :
	State(ac),
	infoBox_(nullptr),
	playButton_(nullptr),
	returnButton_(nullptr),
	mapButtonsPool_(),
	padNavigation_(nullptr),
	bgText_(nullptr),
	housesBackgroundText_(nullptr),
	playButtonText_(nullptr),
	returnButtonText_(nullptr),
	infoBox_(nullptr),
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

	//Recogertexturabotones	
	askName();
	init();
}

MapState::~MapState() {

}

void MapState::init() {
	//returnButton_ = stage->addEntity();
	/*returnButton_->addComponent<Transform>(Vector2D(0, 0));
	returnButton_->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapStateReturnButton));
	returnButton_->addComponent<ButtonBehaviour>();*/
	//stage->addToGroup(returnButton_, ecs::GroupID::Layer1);*/

	Entity* pad = stage->addEntity();
	padNavigation_ = pad->addComponent<ButtonPadNavigation>();
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
		0
		);
	playButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	playButton_->addComponent<ButtonRenderer>(playButtonText_, nullptr);
	stage->addToGroup(playButton_, ecs::GroupID::topLayer);
	stage->addToGroup(infoBox_, ecs::GroupID::topLayer);
	infoBox_->addComponent<MapInfoBoxViewer>();

	for (int x = 0; x < levelsInfo_.size(); x++) {
		Entity* level = stage->addEntity();
		level->addComponent<ButtonBehaviourNC>(infoBox_, levelsInfo_[x]);
		level->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::MapRestaurantButton), nullptr);
		mapButtonsPool_.push_back(level);
	}
	configPadNavigation();
}

void MapState::saveGame()
{
	/*MapConfig mapCFG(playerName_);
	mapCFG.save();*/
}

void MapState::configPadNavigation()
{
	/*padNavigation_->AddButton(mapButtonsPool_.at(0), mapButtonsPool_.at(1), nullptr, nullptr, mapButtonsPool_.at(2));
	padNavigation_->AddButton(mapButtonsPool_.at(1), nullptr, mapButtonsPool_.at(0), nullptr, mapButtonsPool_.at(2));
	padNavigation_->AddButton(mapButtonsPool_.at(2), nullptr, nullptr, mapButtonsPool_.at(1), mapButtonsPool_.at(3));
	padNavigation_->AddButton(mapButtonsPool_.at(3), nullptr, nullptr, mapButtonsPool_.at(2), mapButtonsPool_.at(4));
	padNavigation_->AddButton(mapButtonsPool_.at(4), nullptr, nullptr, mapButtonsPool_.at(2), nullptr);*/
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

