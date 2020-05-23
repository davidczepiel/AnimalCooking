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
	playerName_(""),
	mapCFG("") {

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
	for (auto t : profileTextures) {
		delete t; t = nullptr;
	}
}

void MapState::chooseOption() {
	chooser = stage->addEntity();
	stage->addToGroup(chooser, ecs::GroupID::topLayer);

	MapConfig mapCFG(playerName_);
	if (mapCFG.getProfiles().size() < 10) {
		newGameButton_ = stage->addEntity();
		newGameButton_->addComponent<Transform>(
			Vector2D(5 * casillaX, 2.5 * casillaY),
			Vector2D(),
			6 * casillaX,
			1.5 * casillaY,
			0);
		ButtonBehaviour* bb = newGameButton_->addComponent<ButtonBehaviour>(newGameCallback, app);
		ButtonRenderer* br = newGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), game_->getTextureMngr()->getTexture(Resources::MapNewGameButton));
		bb->setButtonRenderer(br);
		stage->addToGroup(newGameButton_, ecs::GroupID::topLayer);
	}
	else newGameButton_ = nullptr;
	if (mapCFG.getProfiles().size() > 0) {
		loadGameButton_ = stage->addEntity();
		loadGameButton_->addComponent<Transform>(
			Vector2D(5 * casillaX, 4.5 * casillaY),
			Vector2D(),
			6 * casillaX,
			1.5 * casillaY,
			0);
		ButtonBehaviour* bb = loadGameButton_->addComponent<ButtonBehaviour>(loadGameCallback, app);
		ButtonRenderer* br = loadGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), game_->getTextureMngr()->getTexture(Resources::MapLoadGameButton));
		bb->setButtonRenderer(br);
		stage->addToGroup(loadGameButton_, ecs::GroupID::topLayer);
	}
	else loadGameButton_ = nullptr;

	exit = stage->addEntity();
	exit->addComponent<Transform>(
		Vector2D(10, 10),
		Vector2D(),
		2 * casillaX,
		1.5 * casillaY,
		0);
	ButtonBehaviour* bb = exit->addComponent<ButtonBehaviour>(backButtonCallback, app);
	ButtonRenderer* br = exit->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	bb->setButtonRenderer(br);
	stage->addToGroup(exit, ecs::GroupID::topLayer);

	pad = stage->addEntity();
	padNavigation_ = pad->addComponent<ButtonPadNavigation>();

	if (GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)) {
		if (newGameButton_ && loadGameButton_) {
			padNavigation_->AddButton(newGameButton_, exit, loadGameButton_, exit, nullptr);
			padNavigation_->AddButton(loadGameButton_, newGameButton_, nullptr, exit, nullptr);
			padNavigation_->AddButton(exit, nullptr, newGameButton_, nullptr, newGameButton_);
		}
		else if (!loadGameButton_) {
			padNavigation_->AddButton(newGameButton_, exit, nullptr, exit, nullptr);
			padNavigation_->AddButton(exit, nullptr, newGameButton_, nullptr, newGameButton_);
		}
		else {
			padNavigation_->AddButton(loadGameButton_, exit, nullptr, exit, nullptr);
			padNavigation_->AddButton(exit, nullptr, loadGameButton_, nullptr, loadGameButton_);
		}
	}
}

void MapState::init() {

}

void MapState::draw()
{
	bgText_->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
	housesBackgroundText_->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
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
	vector<string> profiles = mapCFG.getProfiles();
	if (profiles.size() > 5) { // En dos columnas
		for (int i = 0; i < profiles.size(); ++i) {
			profileAskers.push_back(stage->addEntity()); // Boton de meterte en partida
			double posX = 0.75 * casillaX;
			double posY = (2 * casillaY) + (1.25 * casillaY * i / 2);
			if (i % 2 == 1) {
				posX = game_->getWindowWidth() - posX - 6.25 * casillaX;
				posY = posY - (0.625 * casillaY);
			}
			profileTextures.push_back(new Texture(game_->getRenderer(), profiles[i],
				game_->getFontMngr()->getFont(Resources::QuarkCheese100), hex2sdlcolor("#FFFFFFFF")));
			profileAskers.back()->addComponent<Transform>(
				Vector2D(posX, posY),
				Vector2D(),
				5 * casillaX,
				1.1 * casillaY,
				0);
			ButtonBehaviourNC* bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(true);
			ButtonRenderer* br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), profileTextures.back());
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);

			profileAskers.push_back(stage->addEntity()); // Boton de eliminar ese perfil
			profileAskers.back()->addComponent<Transform>(
				Vector2D(posX + 5 * casillaX, posY),
				Vector2D(),
				1.1 * casillaX,
				1.1 * casillaY,
				0);
			bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(false, profiles[i]);
			br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
	}
	else { // Una columna
		for (int i = 0; i < profiles.size(); ++i) {
			profileTextures.push_back(new Texture(game_->getRenderer(), profiles[i],
				game_->getFontMngr()->getFont(Resources::QuarkCheese100), hex2sdlcolor("#FFFFFFFF")));

			profileAskers.push_back(stage->addEntity()); // Boton de meterte en partida
			profileAskers.back()->addComponent<Transform>(
				Vector2D(game_->getWindowWidth() / 2 - 4.450 * casillaX, (2 * casillaY) + 1.25 * casillaY * i),
				Vector2D(),
				8 * casillaX,
				1.1 * casillaY,
				0);
			ButtonBehaviourNC* bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(true);
			ButtonRenderer* br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), profileTextures.back());
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);

			profileAskers.push_back(stage->addEntity()); // Boton de eliminar ese perfil
			profileAskers.back()->addComponent<Transform>(
				Vector2D(game_->getWindowWidth() / 2 + 3.375 * casillaX, (2 * casillaY) + 1.25 * casillaY * i),
				Vector2D(),
				1.1 * casillaX,
				1.1 * casillaY,
				0);
			bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(false, profiles[i]);
			br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
	}
}

void MapState::removeProfile(const string& name)
{
	for (int i = 1; i < profileAskers.size(); i += 2) {
		if (GETCMP2(profileAskers[i], ButtonBehaviourNC)->getName() == name) {
			MapConfig mapCFG(name);
			mapCFG.removeProfile();
			GETCMP2(profileAskers[i], ButtonBehaviourNC)->setActive(false);
			GETCMP2(profileAskers[i], ButtonRenderer)->setActive(false);
			GETCMP2(profileAskers[i - 1], ButtonBehaviourNC)->setActive(false);
			GETCMP2(profileAskers[i - 1], ButtonRenderer)->setActive(false);
		}
	}
}

void MapState::setState() {
	hasToBreak = true;
	if (!profileAskers.empty())
		for (auto en : profileAskers) {
			GETCMP2(en, ButtonBehaviourNC)->setActive(false);
			GETCMP2(en, ButtonRenderer)->setActive(false);
		}
	GETCMP2(exit, ButtonBehaviour)->setActive(false);
	GETCMP2(exit, ButtonRenderer)->setActive(false);

	infoBox_ = stage->addEntity();
	playButton_ = stage->addEntity();
	playButton_->addComponent<Transform>(
		Vector2D(3 * casillaX, 1.5 * casillaY),
		Vector2D(),
		3 * casillaX,
		1.5 * casillaY,
		0);

	ButtonBehaviour* bb = playButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	ButtonRenderer* br = playButton_->addComponent<ButtonRenderer>(playButtonText_, nullptr);
	bb->setButtonRenderer(br);
	stage->addToGroup(playButton_, ecs::GroupID::topLayer);
	stage->addToGroup(infoBox_, ecs::GroupID::topLayer);
	infoBox_->addComponent<MapInfoBoxViewer>();

	placeHousesAndButtons();

	configPadNavigation();
}


void MapState::placeHousesAndButtons()
{
	mapCFG = MapConfig(playerName_, isNewGame_);
	vector<levelInfo> levelsInfo_ = mapCFG.getLevelInfoRecipes();

	vector<Transform> transforms_;
	transforms_.push_back(Transform(Vector2D(415, 807), Vector2D(), 80, 40));
	transforms_.push_back(Transform(Vector2D(594, 590), Vector2D(), 40, 20));
	transforms_.push_back(Transform(Vector2D(1008, 820), Vector2D(), 80, 40));
	transforms_.push_back(Transform(Vector2D(1380, 560), Vector2D(), 40, 20));
	transforms_.push_back(Transform(Vector2D(1693, 720), Vector2D(), 70, 35));

	for (int x = 0; x < levelsInfo_.size(); x++) {
		levelButtonsPool_.push_back(stage->addEntity());
		levelButtonsPool_.back()->addComponent<Transform>(transforms_[x]);
		ButtonBehaviourNC* bb = levelButtonsPool_.back()->addComponent<ButtonBehaviourNC>(infoBox_, levelsInfo_[x]);
		ButtonRenderer* br = levelButtonsPool_.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::MapRestaurantButton), nullptr);
		bb->setButtonRenderer(br);
		stage->addToGroup(levelButtonsPool_.back(), ecs::GroupID::topLayer);
	}
}


void MapState::saveGame()
{
	MapConfig mapCFG(playerName_);
	mapCFG.save();
}

void MapState::hideChooseButtons()
{
	if (newGameButton_) {
		GETCMP2(newGameButton_, ButtonBehaviour)->setActive(false);
		GETCMP2(newGameButton_, ButtonRenderer)->setActive(false);
	}
	if (loadGameButton_) {
		GETCMP2(loadGameButton_, ButtonBehaviour)->setActive(false);
		GETCMP2(loadGameButton_, ButtonRenderer)->setActive(false);
	}
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
	MapState* mp = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	int cl = mp->getCurrentLevel();
	if (mp->isCurrentLevelUnlocked())
		SDLGame::instance()->getFSM()->pushState(new ScreenLoader(cl + 2, ac));
}

void MapState::backButtonCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}


void MapState::configPadNavigation() {
	if (GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)) {
		padNavigation_ = pad->addComponent<ButtonPadNavigation>();
		padNavigation_->AddButton(levelButtonsPool_.at(0), levelButtonsPool_.at(1), nullptr, nullptr, levelButtonsPool_.at(2));
		padNavigation_->AddButton(levelButtonsPool_.at(1), nullptr, levelButtonsPool_.at(0), nullptr, levelButtonsPool_.at(2));
		padNavigation_->AddButton(levelButtonsPool_.at(2), nullptr, nullptr, levelButtonsPool_.at(1), levelButtonsPool_.at(3));
		padNavigation_->AddButton(levelButtonsPool_.at(3), nullptr, nullptr, levelButtonsPool_.at(2), levelButtonsPool_.at(4));
		padNavigation_->AddButton(levelButtonsPool_.at(4), nullptr, nullptr, levelButtonsPool_.at(2), nullptr);
	}
}
