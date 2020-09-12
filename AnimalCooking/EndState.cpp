#include "EndState.h"
#include "SDL_macros.h"
#include "LevelViewer.h"
#include "PlayerViewer.h"
#include "Transform.h"
#include "Animator.h"
#include "SDL_macros.h"
#include "ButtonPadNavigation.h"
#include "MapConfig.h"

EndState::EndState(AnimalCooking* ac) :State(ac), score(0), maxScore(SDLGame::instance()->getMaxScore()) {

	SDLGame* game = SDLGame::instance();

	score = game->getScore();

	background = game->getTextureMngr()->getTexture(Resources::BackgroundEndState);

	double casillaX = game->getCasillaX();
	double casillaY = game->getCasillaY();
	int winHeight = game->getWindowHeight();
	int winWidth = game->getWindowWidth();
	int degrees = 7;
	int nextLevelLimit = 45.0;
	jute::jValue& nivel = game->getJsonCurrentLevel();
	if (nivel.hasKey("OneStar"))
		nextLevelLimit = nivel["OneStar"].as_int();

	//maxScore = 150;
	//score = 150*.60;

	createButtons(nextLevelLimit);
	//createPlayers();
	//Creamos la barra de carga con el texto
	Entity* levelViewer = stage->addEntity();
	int twoStarsPerc = 60.0;
	int threeStarsPerc = 80.0;
	jute::jValue& json = SDLGame::instance()->getJsonCurrentLevel();
	if (json.hasKey("TwoStars"))
		twoStarsPerc = json["TwoStars"].as_int();
	if (json.hasKey("ThreeStars"))
		threeStarsPerc = json["ThreeStars"].as_int();
	levelViewer->addComponent<LevelViewer>(500, 1000, 1500, nextLevelLimit, twoStarsPerc, threeStarsPerc, (double)(score) / maxScore);
	stage->addToGroup(levelViewer, ecs::GroupID::ui);



}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame* gameInstance = SDLGame::instance();
	gameInstance->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 3), ac));
	gameInstance->setMaxScore(0);
	gameInstance->setScore(0);
}
void EndState::goToMapState(AnimalCooking* ac) {
	SDLGame* gameInstance = SDLGame::instance();
	gameInstance->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + gameInstance->getRandGen()->nextInt(0, 6), 0);
	FSM* fsm = gameInstance->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}
}
void EndState::goToMenuState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame* gameInstance = SDLGame::instance();
	gameInstance->getFSM()->popState();
	gameInstance->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);
}

void EndState::resetLevel(AnimalCooking* ac)
{
	goToMapState(ac);
	SDLGame* gameInstance = SDLGame::instance();
	gameInstance->getFSM()->pushState(new ScreenLoader(SDLGame::instance()->getCurrentLevel() + 2, ac));
	gameInstance->setMaxScore(0);
	gameInstance->setScore(0);
}

void EndState::createButtons(int nextLevelLimit)
{
	SDLGame* gameInstance = SDLGame::instance();

	double casillaX = gameInstance->getCasillaX();
	double casillaY = gameInstance->getCasillaY();
	int winHeight = gameInstance->getWindowHeight();
	int winWidth = gameInstance->getWindowWidth();
	int degrees = 7;

	Entity* buttonPadNavigation = stage->addEntity();
	ButtonPadNavigation* padNav = buttonPadNavigation->addComponent<ButtonPadNavigation>();
	//------------------>Volver al MapState<---------------------
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(138,
		winHeight - 128),
		Vector2D(),
		64,
		64,
		0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);
	ButtonBehaviour* buttonBehaviour = returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	ButtonRenderer* buttonRenderer = returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapIcon), nullptr);
	buttonBehaviour->setButtonRenderer(buttonRenderer);

	//------------------>Vovler a Jugar<---------------------
	Entity* ResetLevelButton = stage->addEntity();
	stage->addToGroup(ResetLevelButton, ecs::GroupID::Layer1);
	ResetLevelButton->addComponent<Transform>(Vector2D(
		winWidth - 4 * casillaX +
		casillaX / 2,
		3.3 * casillaY - sin(degrees)),
		Vector2D(),
		casillaX / 1.3,
		casillaY / 1.3,
		degrees);
	buttonBehaviour = ResetLevelButton->addComponent<ButtonBehaviour>(resetLevel, app);
	buttonRenderer = ResetLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ReplayIcon), nullptr);
	buttonBehaviour->setButtonRenderer(buttonRenderer);

	//------------------>Siguiente nivel<---------------------
	//Si el score es el suficiente para pasar al siguiente nivel
	Entity* NextLevelButton = nullptr;
	if (score >= (maxScore * nextLevelLimit / 100)) {
		if (SDLGame::instance()->getCurrentLevel() == SDLGame::instance()->getCurrenUnlockLevel() && SDLGame::instance()->getCurrenUnlockLevel() < config::NUM_LEVELS-1) {
			SDLGame::instance()->addCurrentUnlockLevel();
		}

		NextLevelButton = stage->addEntity();
		stage->addToGroup(NextLevelButton, ecs::GroupID::Layer1);
		NextLevelButton->addComponent<Transform>(Vector2D
		(winWidth - 2.5 * casillaX +
			casillaX / 2,
			winHeight - 5 * casillaY -
			casillaY / 2 + sin(degrees)),
			Vector2D(),
			casillaX / 1.3,
			casillaY / 1.3,
			degrees);
		buttonBehaviour = NextLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
		buttonRenderer = NextLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::NextLevelIcon), nullptr);
		buttonBehaviour->setButtonRenderer(buttonRenderer);
		//Ponemos la m�sica de ganar
		gameInstance->getAudioMngr()->playChannel(Resources::AudioId::End_Win, 0);
		padNav->AddButton(NextLevelButton, nullptr, returnToMapButton, ResetLevelButton, nullptr);                   //NextLevel

	}
	else {
		//Ponemos la m�sica de perder
		gameInstance->getAudioMngr()->playChannel(Resources::AudioId::End_Lost, 0);
	}

	//------------------>Volver al MenuPpal<---------------------
	Entity* returnToMenuButton = stage->addEntity();
	stage->addToGroup(returnToMenuButton, ecs::GroupID::Layer1);
	returnToMenuButton->addComponent<Transform>(Vector2D(64,
		winHeight - 128),
		Vector2D(),
		64,
		64,
		0);
	buttonBehaviour = returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);
	buttonRenderer = returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIconEndState), nullptr);
	buttonBehaviour->setButtonRenderer(buttonRenderer);
	//------------------>Navegaci�n por mando<---------------------
	padNav->AddButton(ResetLevelButton, nullptr, returnToMapButton, returnToMapButton, NextLevelButton);         //RestartLevel
	padNav->AddButton(returnToMapButton, ResetLevelButton, nullptr, returnToMenuButton, ResetLevelButton);   //ReturntoMap
	padNav->AddButton(returnToMenuButton, ResetLevelButton, nullptr, nullptr, returnToMapButton);            //ReturnToMainmenu


	//-----------------------------------------------------------------------------------------
}

void EndState::createPlayers()
{
	SDLGame* gameInstance = SDLGame::instance();

	double casillaX = gameInstance->getCasillaX();
	double casillaY = gameInstance->getCasillaY();
	int winHeight = gameInstance->getWindowHeight();
	int winWidth = gameInstance->getWindowWidth();
	//-------------------Player1<-----------------------
	{
		Entity* Player1Idle = stage->addEntity();
		Player1Idle->addComponent<Transform>(Vector2D(
			casillaX * 2.5,
			winHeight - casillaY * 4),
			Vector2D(),
			5 * casillaX,
			5 * casillaY,
			0);
		Animator* p1Anim = Player1Idle->addComponent<Animator>();
		Player1Idle->addComponent<PlayerViewer>(gameInstance->getTextureMngr()->getTexture(Resources::PigIdle), gameInstance->getTextureMngr()->getTexture(Resources::PigWalk), gameInstance->getTextureMngr()->getTexture(Resources::PigAttack));
		stage->addToGroup(Player1Idle, ecs::GroupID::PlayerLayer);
		p1Anim->setCurrentState(Animator::States::Idle);
	}
	//-------------------Player2<-----------------------
	{
		Entity* Player2Idle = stage->addEntity();
		Player2Idle->addComponent<Transform>(Vector2D(
			casillaX * 6,
			winHeight - casillaY * 4),
			Vector2D(),
			5 * casillaX,
			5 * casillaY,
			0);
		Animator* p2Anim = Player2Idle->addComponent<Animator>();
		Player2Idle->addComponent<PlayerViewer>(gameInstance->getTextureMngr()->getTexture(Resources::ChickenIdle), gameInstance->getTextureMngr()->getTexture(Resources::ChickenWalk), gameInstance->getTextureMngr()->getTexture(Resources::ChickenAttack));
		stage->addToGroup(Player2Idle, ecs::GroupID::PlayerLayer);
		p2Anim->setCurrentState(Animator::States::Idle);
	}
}

void EndState::draw()
{
	SDLGame* gameInstance = SDLGame::instance();

	background->render(RECT(0, 0, gameInstance->getWindowWidth(), gameInstance->getWindowHeight()));
	State::draw();
}

void EndState::update() {
	State::update();
	if (InputHandler::instance()->isKeyDown(SDL_Scancode::SDL_SCANCODE_ESCAPE)) {
		goToMapState(app);
	}
}