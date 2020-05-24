#include "MapState.h"
#include "ScreenLoader.h"
#include "SDL_macros.h"
#include "FSM.h"
#include "ButtonRenderer.h"
#include "ButtonRendererHouse.h"
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
	chooser(nullptr),
	profileAskers(),
	maxLevels_(0),
	currentLevel_(0),
	lastLevel_(0),
	playerName_("")
{
	game_ = SDLGame::instance();
	maxLevels_ = game_->getMaxLevels();
	casillaX = game_->getCasillaX();
	casillaY = game_->getCasillaY();
	//Background textures
	bgText_ = game_->getTextureMngr()->getTexture(Resources::MapStateBackground);
	housesBackgroundText_ = game_->getTextureMngr()->getTexture(Resources::MapStateHousesBackground);
	//Play and return buttons textures
	playButtonText_ = new Texture(game_->getRenderer(), "PLAY", game_->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor("#000000ff"));
	chooseOption();
	
}

MapState::~MapState() {
	for (auto t : profileTextures) {
		delete t; t = nullptr;
	}
	delete playButtonText_; playButtonText_ = nullptr;
	game_->removeLevelInfos();
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
	ButtonRenderer* br = exit->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), game_->getTextureMngr()->getTexture(Resources::Back));
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
	GPadController* gpad = GPadController::instance();
	if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->buttonJustPressed()) {
		if (playButton_ != nullptr &&  (gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_A) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_A))) {
			GETCMP2(playButton_, ButtonBehaviour)->action();
		}
		if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_B) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_B))) {
			backButtonCallback(getAnimalCooking());
		}
	}

}


void MapState::askName() {
	nameAsker = stage->addEntity();
	nameAsker->addComponent<NameAsker>();
	stage->addToGroup(nameAsker, ecs::GroupID::topLayer);
}


void MapState::askProfile()
{
	MapConfig mapCFG = (playerName_);
	vector<string> profiles = mapCFG.getProfiles();
	padNavigation_->resetNavigation();
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
			ButtonBehaviourNC* bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(true, profiles[i]);
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
		prepareNavPadFewProfiles(true);
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
			ButtonBehaviourNC* bb = profileAskers.back()->addComponent<ButtonBehaviourNC>(true, profiles[i]);
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
		prepareNavPadFewProfiles(false);
	}
}


void MapState::prepareNavPadFewProfiles(bool muchos)
{
	padNavigation_->AddButton(exit, nullptr, profileAskers.at(0), nullptr, profileAskers.at(0));
	int jump;
	if (muchos) jump = 4;
	else jump = 2;
	//Bucle para meter la navegación de cada botón
	Entity* up;
	Entity* down;
	Entity* left;
	Entity* right;
	for (int i = 0; i < profileAskers.size(); i++) {
		int indice = i;
		//Arriba
		indice = i - jump;
		if (indice < 0) up = exit;
		else up = profileAskers.at(indice);
		indice = i;

		//Abajo
		indice = i + jump;
		if (indice > profileAskers.size() - 1) down = exit;
		else down = profileAskers.at(indice);
		indice = i;

		//Izquierda
		indice = i - 1;
		if (indice < 0) left = exit;
		else left = profileAskers.at(indice);
		indice = i;

		//Derecha
		indice = i + 1;
		if (indice > profileAskers.size() - 1) right = exit;
		else right = profileAskers.at(indice);
		indice = i;

		padNavigation_->AddButton(profileAskers.at(i), up, down, left, right);
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

	MapConfig mapCFG(playerName_, isNewGame_);
	game_->setLevelInfos(mapCFG.getLevelInfoRecipes());
	levelinfos_ = game_->getLevelInfos();

	infoBox_ = stage->addEntity();
	playButton_ = stage->addEntity();
	playButton_->addComponent<Transform>(
		Vector2D(4 * casillaX, 2.3 * casillaY),
		Vector2D(),
		2 * casillaX,
		0.75 * casillaY,
		0);

	playButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	playButton_->addComponent<ButtonRendererHouse>(game_->getTextureMngr()->getTexture(Resources::MapStatePlayButton), playButtonText_, game_->getLevelInfos()->at(0));
	stage->addToGroup(playButton_, ecs::GroupID::topLayer);
	stage->addToGroup(infoBox_, ecs::GroupID::ui);
	infoBox_->addComponent<MapInfoBoxViewer>();

	//Exit button
	returnButton_ = stage->addEntity();
	returnButton_->addComponent<Transform>(
		Vector2D(1550, 965),
		Vector2D(),
		0.6 * casillaX,
		0.6 * casillaY,
		0);
	ButtonBehaviour* bb = returnButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	ButtonRenderer* br = returnButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::HomeIconMapState), nullptr);
	bb->setButtonRenderer(br);
	stage->addToGroup(returnButton_, ecs::GroupID::topLayer);

	placeHousesAndButtons();

	configPadNavigation();

	MapConfig mpCFG;
	mpCFG.saveNewProfile(playerName_);
}


void MapState::placeHousesAndButtons()
{
	MapInfoBoxViewer* mInfo = GETCMP2(infoBox_, MapInfoBoxViewer);
	mInfo->setCurrentInfoLevel(levelinfos_->at(0));

	vector<Transform> transforms_;
	transforms_.push_back(Transform(Vector2D(415, 807), Vector2D(), 80, 40));
	transforms_.push_back(Transform(Vector2D(594, 590), Vector2D(), 40, 20));
	transforms_.push_back(Transform(Vector2D(1008, 820), Vector2D(), 80, 40));
	transforms_.push_back(Transform(Vector2D(1380, 560), Vector2D(), 40, 20));
	transforms_.push_back(Transform(Vector2D(1693, 720), Vector2D(), 70, 35));

	for (int x = 0; x < levelinfos_->size(); x++) {
		levelButtonsPool_.push_back(stage->addEntity());
		levelButtonsPool_.back()->addComponent<Transform>(transforms_[x]);
		ButtonBehaviourNC* bb = levelButtonsPool_.back()->addComponent<ButtonBehaviourNC>(infoBox_, levelinfos_->at(x));
		ButtonRendererHouse* br = levelButtonsPool_.back()->addComponent<ButtonRendererHouse>(game_->getTextureMngr()->getTexture(Resources::MapRestaurantButton), nullptr, levelinfos_->at(x));
		stage->addToGroup(levelButtonsPool_.back(), ecs::GroupID::topLayer);
	}
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

		padNavigation_ = GETCMP2(pad, ButtonPadNavigation);
		padNavigation_->resetNavigation();

		int i = 0;
		while (i < levelinfos_->size() && levelinfos_->at(i)->unlocked) {
			Entity* behind = nullptr;
			Entity* forward = nullptr;
			if (i > 0 && levelinfos_->at(i - 1)->unlocked)
				behind = levelButtonsPool_.at(i - 1);
			if (i < levelinfos_->size() - 1 && levelinfos_->at(i + 1)->unlocked)
				forward = levelButtonsPool_.at(i + 1);
			padNavigation_->AddButton(levelButtonsPool_.at(i), nullptr, nullptr, behind, forward);
			i++;
		}
	}
}
