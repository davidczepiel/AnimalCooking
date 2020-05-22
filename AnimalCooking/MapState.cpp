#include "MapState.h"
#include "ScreenLoader.h"
#include "SDL_macros.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonBehaviourNC.h"
#include "MapConfig.h"
#include "ButtonPadNavigation.h"

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
	chooser(nullptr),
	profileAskers(),
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
	saveGame();

}

void MapState::chooseOption() {
	chooser = stage->addEntity();
	stage->addToGroup(chooser, ecs::GroupID::topLayer);

	newGameButton_ = stage->addEntity();
	newGameButton_->addComponent<Transform>(
		Vector2D(5 * casillaX, 2.5 * casillaY),
		Vector2D(),
		6 * casillaX,
		1.5 * casillaY,
		0);
	newGameButton_->addComponent<ButtonBehaviour>(newGameCallback, app);
	newGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), game_->getTextureMngr()->getTexture(Resources::MapNewGameButton));
	stage->addToGroup(newGameButton_, ecs::GroupID::topLayer);

	loadGameButton_ = stage->addEntity();
	loadGameButton_->addComponent<Transform>(
		Vector2D(5 * casillaX, 4.5 * casillaY),
		Vector2D(),
		6 * casillaX,
		1.5 * casillaY,
		0);
	loadGameButton_->addComponent<ButtonBehaviour>(loadGameCallback, app);
	loadGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), game_->getTextureMngr()->getTexture(Resources::MapLoadGameButton));
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
	nameAsker = stage->addEntity();
	nameAsker->addComponent<NameAsker>();
	stage->addToGroup(nameAsker, ecs::GroupID::topLayer);
}


void MapState::askProfile()
{
	MapConfig mapCFG(playerName_);
	vector<string>& profiles = mapCFG.getProfiles();
	if (profiles.size() > 5) { // En dos columnas
		for (int i = 0; i < profiles.size(); ++i) {
			profileAskers.push_back(stage->addEntity()); // Boton de meterte en partida
			double posX = 0.75 * casillaX;
			double posY = (0.875 * casillaY) + 1.5 * casillaY * i;
			if (i % 2 == 1) {
				posX = game_->getWindowWidth() - posX - 7.25 * casillaX;
				posY = posY - 1.5 * casillaY;
			}
			profileAskers.back()->addComponent<Transform>(
				Vector2D(posX, posY),
				Vector2D(),
				6 * casillaX, 
				1.25 * casillaY, 
				0);
			profileAskers.back()->addComponent<ButtonBehaviourNC>(true);
			profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);

			profileAskers.push_back(stage->addEntity()); // Boton de eliminar ese perfil
			profileAskers.back()->addComponent<Transform>(
				Vector2D(posX + 6 * casillaX, posY),
				Vector2D(),
				1.25 * casillaX,
				1.25 * casillaY,
				0);
			profileAskers.back()->addComponent<ButtonBehaviourNC>(false);
			profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
	}
	else { // Una columna
		for (int i = 0; i < profiles.size(); ++i) {
			profileAskers.push_back(stage->addEntity()); // Boton de meterte en partida
			profileAskers.back()->addComponent<Transform>(
				Vector2D(game_->getWindowWidth() - 4.625 * casillaX, (0.875 * casillaY) + 1.5 * casillaY * i),
				Vector2D(),
				8 * casillaX,
				1.25 * casillaY,
				0);
			profileAskers.back()->addComponent<ButtonBehaviourNC>(true); 
			profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);

			profileAskers.push_back(stage->addEntity()); // Boton de eliminar ese perfil
			profileAskers.back()->addComponent<Transform>(
				Vector2D(game_->getWindowWidth() + 3.375 * casillaX, (0.875 * casillaY) + 1.5 * casillaY * i),
				Vector2D(),
				1.25 * casillaX,
				1.25 * casillaY,
				0);
			profileAskers.back()->addComponent<ButtonBehaviourNC>(false);
			profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
	}
}

void MapState::setState() {
	hasToBreak = true;
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
	vector<levelInfo> levelsInfo_;

	MapConfig mapCFG(playerName_, isNewGame_);
	levelsInfo_ = mapCFG.getLevelInfoRecipes();


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

void MapState::hideChooseButtons()
{
	GETCMP2(newGameButton_, ButtonBehaviour)->setActive(false);
	GETCMP2(newGameButton_, ButtonRenderer)->setActive(false);
	GETCMP2(loadGameButton_, ButtonBehaviour)->setActive(false);
	GETCMP2(loadGameButton_, ButtonRenderer)->setActive(false);
}

void MapState::newGameCallback(AnimalCooking* ac)
{
	MapState* ms = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	ms->isNewGame();
	ms->hideChooseButtons();
	ms->askName();
	ms->hasToBreak = true;
}

void MapState::loadGameCallback(AnimalCooking* ac)
{
	MapState* ms = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	ms->isNotNewGame();
	ms->hideChooseButtons();
	ms->askProfile();
	ms->hasToBreak = true;
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


void MapState::configPadNavigation() {
	Entity* pad = stage->addEntity();
	padNavigation_ = pad->addComponent<ButtonPadNavigation>();

	padNavigation_->AddButton(levelButtonsPool_.at(0), levelButtonsPool_.at(1), nullptr, nullptr, levelButtonsPool_.at(2));
	padNavigation_->AddButton(levelButtonsPool_.at(1), nullptr, levelButtonsPool_.at(0), nullptr, levelButtonsPool_.at(2));
	padNavigation_->AddButton(levelButtonsPool_.at(2), nullptr, nullptr, levelButtonsPool_.at(1), levelButtonsPool_.at(3));
	padNavigation_->AddButton(levelButtonsPool_.at(3), nullptr, nullptr, levelButtonsPool_.at(2), levelButtonsPool_.at(4));
	padNavigation_->AddButton(levelButtonsPool_.at(4), nullptr, nullptr, levelButtonsPool_.at(2), nullptr);
}
