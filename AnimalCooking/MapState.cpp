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
	nameAsker(nullptr),	
	infoBox_(nullptr),
	playButton_(nullptr),
	nextScreenButton_(nullptr),
	PreviousScreenButton_(nullptr),
	returnButton_(nullptr),
	levelButtonsPool_(),
	padNavigation_(nullptr),
	bgText_(vector<Texture*>()),
	playButtonText_(nullptr),
	chooser(nullptr),
	profileAskers(),
	maxLevels_(0),
	currentLevel_(0),
	levelPacks_(6),
	lastLevel_(0),
	playerName_(""),
	totalStars_(nullptr),
	starsWarningActive_(false),
	jsonGeneral(SDLGame::instance()->getJsonGeneral())
{
	game_ = SDLGame::instance();
	maxLevels_ = game_->getMaxLevels();
	casillaX = game_->getCasillaX();
	casillaY = game_->getCasillaY();
	//Background textures
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapStateBackground));
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapState2Background));
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapState3Background));
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapState4Background));
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapState5Background));
	bgText_.push_back(game_->getTextureMngr()->getTexture(Resources::MapState6Background));
	//Play and return buttons textures
	playButtonText_ = new Texture(game_->getRenderer(), "PLAY", game_->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor("#ffffffff"));
	//Estrellas y panel estrellas
	starScore_ = game_->getTextureMngr()->getTexture(Resources::YellowStar);
	starScoreBackground_ = game_->getTextureMngr()->getTexture(Resources::Star);
	panelStars_ = game_->getTextureMngr()->getTexture(Resources::MapStateStarBox);
	//
	starScoreRect_ = RECT(game_->getWindowWidth() - 300, 10, 100, 100);
	starScoreBackGroundRect_ = RECT(game_->getWindowWidth() - 305, 5, 110, 110);
	totalStarsRect_ = RECT(game_->getWindowWidth() - 195, 5, 195, 110);
	starPanelRect_ = RECT(game_->getWindowWidth() - 310, 0, 310, 120);

	chooseOption();
}

MapState::~MapState() {
	for (auto t : profileTextures) {
		delete t; t = nullptr;
	}
	if (totalStars_ != nullptr) delete totalStars_;
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
			Vector2D(5 * casillaX, 4.5 * casillaY),
			Vector2D(),
			6 * casillaX,
			1.5 * casillaY,
			0);
		ButtonBehaviour* bb = newGameButton_->addComponent<ButtonBehaviour>(newGameCallback, app);
		ButtonRenderer* br = newGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig), game_->getTextureMngr()->getTexture(Resources::MapNewGameButton));
		bb->setButtonRenderer(br);
		stage->addToGroup(newGameButton_, ecs::GroupID::topLayer);
	}
	else newGameButton_ = nullptr;
	if (mapCFG.getProfiles().size() > 0) {
		loadGameButton_ = stage->addEntity();
		loadGameButton_->addComponent<Transform>(
			Vector2D(5 * casillaX, 2.5 * casillaY),
			Vector2D(),
			6 * casillaX,
			1.5 * casillaY,
			0);
		ButtonBehaviour* bb = loadGameButton_->addComponent<ButtonBehaviour>(loadGameCallback, app);
		ButtonRenderer* br = loadGameButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig), game_->getTextureMngr()->getTexture(Resources::MapLoadGameButton));
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
	ButtonRenderer* br = exit->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig), game_->getTextureMngr()->getTexture(Resources::Back));
	bb->setButtonRenderer(br);
	stage->addToGroup(exit, ecs::GroupID::topLayer);

	pad = stage->addEntity();


	if (GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)) {
		padNavigation_ = pad->addComponent<ButtonPadNavigation>();
		if (newGameButton_ && loadGameButton_) {
			padNavigation_->AddButton(loadGameButton_, exit, newGameButton_, exit, nullptr);
			padNavigation_->AddButton(newGameButton_, loadGameButton_, nullptr, exit, nullptr);
			padNavigation_->AddButton(exit, nullptr, loadGameButton_, nullptr, loadGameButton_);
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
	if (transition_) {
		SDL_Rect aux = RECT(xTransition_, 0, game_->getWindowWidth(), game_->getWindowHeight());
		if (transitionDirection_ < 0) {
			bgText_[currentMapScene_]->render(RECT(xTransition_, 0, game_->getWindowWidth(), game_->getWindowHeight()));
			bgText_[currentMapScene_ - 1]->render(RECT(xTransition_ - game_->getWindowWidth(), 0, game_->getWindowWidth(), game_->getWindowHeight()));
		}
		else {
			bgText_[currentMapScene_]->render(RECT(xTransition_, 0, game_->getWindowWidth(), game_->getWindowHeight()));
			bgText_[currentMapScene_ + 1]->render(RECT(xTransition_ + game_->getWindowWidth(), 0, game_->getWindowWidth(), game_->getWindowHeight()));
		}
	}
	else {
		bgText_[currentMapScene_]->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
	}
	if (inMap) {
		panelStars_->render(starPanelRect_);
		starScoreBackground_->render(starScoreBackGroundRect_);
		starScore_->render(starScoreRect_);
		totalStars_->render(totalStarsRect_);
	}
	
	State::draw();
}

void MapState::update()
{
	if (transition_) {

		xTransition_ += transitionVelocity_ * transitionDirection_;
		if ((transitionDirection_ == 1 && xTransition_ >= 0) || (transitionDirection_ == -1 && xTransition_ <= 0)) {	//Termina la transicion
			transitionEnd();
		}
	}
	else {
		GPadController* gpad = GPadController::instance();
		if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->isAnyButtonJustPressed()) {

			if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_A) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_A))) {
				if (playButton_ != nullptr) {
					Entity* e = padNavigation_->getObjectInFocus();
					if ( e!= nullptr && GETCMP2(e, ButtonBehaviourNC) != nullptr) {
						GETCMP2(playButton_, ButtonBehaviour)->action();
					}
				}
				else if (nameAsker != nullptr) {
					NameAsker* na = GETCMP2(nameAsker, NameAsker);
					if (na->getActive() && na->getName().size() > 1) {
						na->setActive(false);
						setName(na->getName());
						setState();
					}
				}
			}
			else if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_B) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_B))) {
				backButtonCallback(getAnimalCooking());
			}

		}
		for (auto& e : stage->getEntites()) {
			if (!hasToBreak)
				e->update();
			else break;
		}
		hasToBreak = false;
	}

	if(starsWarningActive_) {
		if (phase_) {
			starScoreRect_.x--; starScoreRect_.w++; starScoreRect_.h++;
			starPanelRect_.x--; starPanelRect_.w++; starPanelRect_.h++;
			totalStarsRect_.x--; totalStarsRect_.w++; totalStarsRect_.h++;
			starScoreBackGroundRect_.x--; starScoreBackGroundRect_.w++; starScoreBackGroundRect_.h++;
			if (game_->getTime() - auxTime_ >= 250) {
				phase_ = false;
				auxTime_ = game_->getTime();
			}
		}
		else {
			starScoreRect_.x++; starScoreRect_.w--; starScoreRect_.h--;
			starPanelRect_.x++; starPanelRect_.w--; starPanelRect_.h--;
			totalStarsRect_.x++; totalStarsRect_.w--; totalStarsRect_.h--;
			starScoreBackGroundRect_.x++; starScoreBackGroundRect_.w--; starScoreBackGroundRect_.h--;
			if (game_->getTime() - auxTime_ >= 250) {
				phase_ = true;
				starsWarningActive_ = false;
				starScoreRect_ = RECT(game_->getWindowWidth() - 300, 10, 100, 100);
				starScoreBackGroundRect_ = RECT(game_->getWindowWidth() - 305, 5, 110, 110);
				totalStarsRect_ = totalStarsRectAux_;
				starPanelRect_ = RECT(game_->getWindowWidth() - 310, 0, 310, 120);
			}
		}
	}

	if (InputHandler::instance()->isKeyDown(SDL_Scancode::SDL_SCANCODE_ESCAPE)) {
		backButtonCallback(app);
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
	if(padNavigation_!= nullptr) padNavigation_->resetNavigation();
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
			ButtonRenderer* br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig), profileTextures.back());
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
			br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonBin), nullptr);
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
		if (padNavigation_ != nullptr) prepareNavPadFewProfiles(true);
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
			ButtonRenderer* br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig), profileTextures.back());
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
			br = profileAskers.back()->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonBin), nullptr);
			bb->setButtonRenderer(br);
			stage->addToGroup(profileAskers.back(), ecs::GroupID::topLayer);
		}
		if (padNavigation_ != nullptr) prepareNavPadFewProfiles(false);
	}
}


void MapState::prepareNavPadFewProfiles(bool muchos)
{
	int jump;
	if (muchos) jump = 4;
	else jump = 2;
	//Bucle para meter la navegaci�n de cada bot�n
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
	padNavigation_->AddButton(exit, nullptr, profileAskers.at(0), nullptr, profileAskers.at(0));
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

void MapState::transitionEnd()
{
	xTransition_ = 0;
	transition_ = false;


	if (currentMapScene_ == 5)
	{
		MapConfig aux(playerName_, false);

		for (auto b : levelButtonsPool_)
		{
			GETCMP2(b, ButtonBehaviourNC)->setActive(false);
			GETCMP2(b, ButtonRendererHouse)->setActive(false);

		}

		ButtonBehaviourNC* bnc = GETCMP2(levelButtonsPool_.at(0), ButtonBehaviourNC);
		bnc->setActive(true);
		bnc->setLevelInfo(levelinfos_->back());

		ButtonRendererHouse* brh = GETCMP2(levelButtonsPool_.at(0), ButtonRendererHouse);
		brh->setActive(true);

		Transform* levelITransform = GETCMP2(levelButtonsPool_.at(0), Transform);
		levelITransform->setPos(aux.getLevelInfoRecipes().back().buttonPosition);
		levelITransform->setW(aux.getLevelInfoRecipes().back().buttonsSize.getX());
		levelITransform->setH(aux.getLevelInfoRecipes().back().buttonsSize.getY());
	}
	


	if (currentMapScene_ != 5)
	{
		for (auto& e : levelButtonsPool_) {
			GETCMP2(e, ButtonRendererHouse)->setActive(true);
			GETCMP2(e, ButtonBehaviourNC)->setActive(true);
		}
	}


	GETCMP2(infoBox_, MapInfoBoxViewer)->setActive(true);
	GETCMP2(returnButton_, ButtonRenderer)->setActive(true);
	GETCMP2(playButton_, ButtonRendererHouse)->setActive(true);

	//-----Activar/desactivar botones de desplazamiento del mapstate------------
	if (currentMapScene_ == 0) {
		GETCMP2(PreviousScreenButton_, ButtonRenderer)->setActive(false);
		GETCMP2(PreviousScreenButton_, ButtonBehaviour)->setActive(false);
	}
	else {
		GETCMP2(PreviousScreenButton_, ButtonRenderer)->setActive(true);
		GETCMP2(PreviousScreenButton_, ButtonBehaviour)->setActive(true);
	}

	if (currentMapScene_ == bgText_.size() - 1) {
		GETCMP2(nextScreenButton_, ButtonRenderer)->setActive(false);
		GETCMP2(nextScreenButton_, ButtonBehaviour)->setActive(false);
	}
	else {
		GETCMP2(nextScreenButton_, ButtonRenderer)->setActive(true);
		GETCMP2(nextScreenButton_, ButtonBehaviour)->setActive(true);
	}

	if (jsonGeneral["MapStars"][to_string(currentMapScene_ + 1)].as_int() > SDLGame::instance()->getNumStars()) {	//si aun no se han superado el minimo de estrellas se desactiva
		static_cast<ButtonRendererMapArrow*>(GETCMP2(nextScreenButton_, ButtonRenderer))->setAvailable(false);
		GETCMP2(nextScreenButton_, ButtonBehaviour)->setActive(false);
	}

}

void MapState::nextScreen()
{
	if (currentMapScene_ >= bgText_.size() - 1) return;

	transition_ = true;
	transitionDirection_ = -1;
	xTransition_ = game_->getWindowWidth();
	currentMapScene_++;
	for (auto& e:levelButtonsPool_)
	{
		GETCMP2(e, ButtonRendererHouse)->setActive(false);
	}
	GETCMP2(returnButton_, ButtonRenderer)->setActive(false);
	GETCMP2(infoBox_, MapInfoBoxViewer)->setActive(false);
	GETCMP2(playButton_, ButtonRendererHouse)->setActive(false);
	GETCMP2(nextScreenButton_, ButtonRenderer)->setActive(false);
	GETCMP2(PreviousScreenButton_, ButtonRenderer)->setActive(false);
	refreshHousesAndButtons();
	configPadNavigation();

}

void MapState::previousScreen()
{
	if (currentMapScene_ < 1) return;

	transition_ = true;
	transitionDirection_ = 1;
	xTransition_ = -game_->getWindowWidth();
	currentMapScene_--;
	for (auto& e : levelButtonsPool_)
	{
		GETCMP2(e, ButtonRendererHouse)->setActive(false);
	}
	GETCMP2(infoBox_, MapInfoBoxViewer)->setActive(false);
	GETCMP2(playButton_, ButtonRendererHouse)->setActive(false);
	GETCMP2(returnButton_, ButtonRenderer)->setActive(false);
	GETCMP2(nextScreenButton_, ButtonRenderer)->setActive(false);
	GETCMP2(PreviousScreenButton_, ButtonRenderer)->setActive(false);
	refreshHousesAndButtons();
	configPadNavigation();

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
		Vector2D(4.7 * casillaX, 2.3 * casillaY),
		Vector2D(),
		2 * casillaX,
		0.75 * casillaY,
		0);

	playButton_->addComponent<ButtonBehaviour>(screenLoaderCallback, app);
	playButton_->addComponent<ButtonRendererHouse>(game_->getTextureMngr()->getTexture(Resources::MapStatePlayButton), playButtonText_, game_->getLevelInfos()->at(0));
	stage->addToGroup(playButton_, ecs::GroupID::topLayer);
	stage->addToGroup(infoBox_, ecs::GroupID::ui);
	infoBox_->addComponent<MapInfoBoxViewer>(GETCMP2(playButton_, Transform));

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

	inMap = true;
	if (totalStars_ != nullptr) delete totalStars_;
	totalStars_ = new Texture(game_->getRenderer(), to_string(game_->getNumStars()), game_->getFontMngr()->getFont(Resources::FontId::QuarkCheese100), hex2sdlcolor("#ffffffff"));
	if (game_->getNumStars() < 10) totalStarsRect_.w = 97;
	else totalStarsRect_.w = 195;

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
	transforms_.push_back(Transform(Vector2D(350, 800), Vector2D(), 80, 100));
	transforms_.push_back(Transform(Vector2D(594, 570), Vector2D(), 40, 50));
	transforms_.push_back(Transform(Vector2D(1000, 780), Vector2D(), 80, 100));
	transforms_.push_back(Transform(Vector2D(1380, 530), Vector2D(), 40, 50));
	transforms_.push_back(Transform(Vector2D(1693, 690), Vector2D(), 70, 88));
	transforms_.push_back(Transform(Vector2D(950, 470), Vector2D(), 46, 58));

	for (int x = 0; x < levelPacks_; x++) {
		levelButtonsPool_.push_back(stage->addEntity());
		levelButtonsPool_.back()->addComponent<Transform>(transforms_[x]);
		ButtonBehaviourNC* bb = levelButtonsPool_.back()->addComponent<ButtonBehaviourNC>(infoBox_, levelinfos_->at(x));
		ButtonRendererHouse* br = levelButtonsPool_.back()->addComponent<ButtonRendererHouse>(game_->getTextureMngr()->getTexture(Resources::MapRestaurantButton), nullptr, levelinfos_->at(x));
		stage->addToGroup(levelButtonsPool_.back(), ecs::GroupID::topLayer);
	}

	nextScreenButton_ = stage->addEntity();
	Texture* aux = game_->getTextureMngr()->getTexture(Resources::ButtonNext);
	nextScreenButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() - aux->getWidth(), (game_->getWindowHeight() / 2)), Vector2D(0, 0), aux->getWidth() - 60, aux->getHeight() + aux->getHeight()/3);
	ButtonBehaviour* bb = nextScreenButton_->addComponent<ButtonBehaviour>(nextScreenCallBack, app);
	ButtonRenderer* br = nextScreenButton_->addComponent<ButtonRendererMapArrow>(game_->getTextureMngr()->getTexture(Resources::ButtonNext), nullptr);
	bb->setButtonRenderer(br);
	stage->addToGroup(nextScreenButton_, ecs::GroupID::topLayer);
	if (currentMapScene_ == bgText_.size() - 1) {
		br->setActive(false);
		bb->setActive(false);
	}
	if (jsonGeneral["MapStars"][to_string(currentMapScene_ + 1)].as_int() > SDLGame::instance()->getNumStars()) {	//si aun no se han superado el minimo de estrellas se desactiva
		static_cast<ButtonRendererMapArrow*>(br)->setAvailable(false);
		bb->setActive(false);
	}
	static_cast<ButtonRendererMapArrow*>(br)->updateText(jsonGeneral["MapStars"][to_string(currentMapScene_ + 1)].as_int());

	PreviousScreenButton_ = stage->addEntity();
	PreviousScreenButton_->addComponent<Transform>(Vector2D(30, (game_->getWindowHeight() / 2)), Vector2D(0, 0), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = PreviousScreenButton_->addComponent<ButtonBehaviour>(previousScreenCallBack, app);
	br = PreviousScreenButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonPrev), nullptr);
	bb->setButtonRenderer(br);
	stage->addToGroup(PreviousScreenButton_, ecs::GroupID::topLayer);
	if (currentMapScene_ == 0) {
		br->setActive(false); 
		bb->setActive(false);
	}

	aux = nullptr;
	bb = nullptr;
	br = nullptr;
}

void MapState::refreshHousesAndButtons()
{
	MapConfig aux(playerName_,false);
	

	if (currentMapScene_ < 5)
	{
		for (int i = 0; i < levelPacks_; i++)
		{
			int newI = currentMapScene_ * levelPacks_ + i;
			//me quedo con el nivel que lo0 toca al boton y se lo paso a sus componentes para que se adapten si esta desbloqueado o no
			levelInfo* actualLevel = levelinfos_->at(newI);
			GETCMP2(levelButtonsPool_.at(i), ButtonBehaviourNC)->setLevelInfo(actualLevel);
			GETCMP2(levelButtonsPool_.at(i), ButtonRendererHouse)->setLevel(actualLevel);
			Transform* levelITransform = GETCMP2(levelButtonsPool_.at(i), Transform);
			levelITransform->setPos(aux.getLevelInfoRecipes().at(newI).buttonPosition);
			levelITransform->setW(aux.getLevelInfoRecipes().at(newI).buttonsSize.getX());
			levelITransform->setH(aux.getLevelInfoRecipes().at(newI).buttonsSize.getY());
		}

		if (jsonGeneral["MapStars"][to_string(currentMapScene_ + 1)].as_int() > SDLGame::instance()->getNumStars()) {	//si aun no se han superado el minimo de estrellas se desactiva
			static_cast<ButtonRendererMapArrow*>(GETCMP2(nextScreenButton_, ButtonRenderer))->setAvailable(false);
			static_cast<ButtonRendererMapArrow*>(GETCMP2(nextScreenButton_, ButtonRenderer))->updateText(jsonGeneral["MapStars"][to_string(currentMapScene_ + 1)].as_int());
			GETCMP2(nextScreenButton_, ButtonBehaviour)->setActive(false);
		}
		else {
			static_cast<ButtonRendererMapArrow*>(GETCMP2(nextScreenButton_, ButtonRenderer))->setAvailable(true);
			GETCMP2(nextScreenButton_, ButtonBehaviour)->setActive(true);
		}

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
	MapState* mp = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	int cl = mp->getCurrentLevel();
	if (mp->isCurrentLevelUnlocked()) {
		SDLGame::instance()->getAudioMngr()->haltMusic();
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
		SDLGame::instance()->getFSM()->pushState(new ScreenLoader(cl + 2, ac));
	}
}

void MapState::backButtonCallback(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void MapState::nextScreenCallBack(AnimalCooking* ac) {
	MapState* ms = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	ms->nextScreen();
}

void MapState::previousScreenCallBack(AnimalCooking* ac)
{
	MapState* ms = static_cast<MapState*>(SDLGame::instance()->getFSM()->currentState());
	ms->previousScreen();
}

void MapState::notEnoughStarsWarning()
{
	if (starsWarningActive_) return;
	starsWarningActive_ = true;
	auxTime_ = game_->getTime();
	totalStarsRectAux_ = totalStarsRect_;
}

void MapState::configPadNavigation() {
	if (GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)) {

		padNavigation_ = GETCMP2(pad, ButtonPadNavigation);
		padNavigation_->resetNavigation();

		int i = 0;
		while (i < levelPacks_ && levelinfos_->at((currentMapScene_ * levelPacks_)+i)->unlocked) {
			Entity* behind = nullptr;
			Entity* forward = nullptr;
			if (i > 0 && levelinfos_->at((currentMapScene_*levelPacks_)+ i - 1)->unlocked)
				behind = levelButtonsPool_.at(i - 1);
			if (i < levelPacks_ - 1 && levelinfos_->at((currentMapScene_ * levelPacks_) + i + 1)->unlocked)
				forward = levelButtonsPool_.at(i + 1);
			padNavigation_->AddButton(levelButtonsPool_.at(i), nullptr, nullptr, behind, forward);
			i++;
		}
		if(currentMapScene_>0)
		padNavigation_->addButtonToAnExistingOne(PreviousScreenButton_,nullptr,nullptr,nullptr,levelButtonsPool_.at(0), levelButtonsPool_.at(0),2);
		if(currentMapScene_<5 && GETCMP2(levelButtonsPool_.at(i - 1), ButtonBehaviourNC)->getLevelInfo()->unlocked)
		padNavigation_->addButtonToAnExistingOne(nextScreenButton_, nullptr, nullptr,levelButtonsPool_.at(i-1),nullptr, levelButtonsPool_.at(i - 1),3);
	}
}
