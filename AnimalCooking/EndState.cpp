#include "EndState.h"
#include "SDL_macros.h"
#include "LevelViewer.h"
#include "PlayerViewer.h"
#include "Transform.h"
#include "Animator.h"

EndState::EndState(AnimalCooking* ac) :State(ac),score(0),maxScore(SDLGame::instance()->getMaxScore()) {

	score=SDLGame::instance()->getScore();

	background= SDLGame::instance()->getTextureMngr()->getTexture(Resources::BackgroundEndState);

	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();
	int winHeight = SDLGame::instance()->getWindowHeight();
	int winWidth = SDLGame::instance()->getWindowWidth();
	int degrees = 7;
	int nextLevelLimit = 50;
	
	score = 120;
	maxScore = 150;

	createButtons();
	//createPlayers();
	//Creamos la barra de carga con el texto
	Entity* lv = stage->addEntity();
	lv->addComponent<LevelViewer>(500, 1000, 1500, nextLevelLimit, 75, 95,(double)(score)/maxScore);
	stage->addToGroup(lv, ecs::GroupID::ui);


}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 1), ac));
	SDLGame::instance()->setMaxScore(0);
	SDLGame::instance()->setScore(0);
}
void EndState::goToMapState(AnimalCooking* ac) {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	FSM* fsm = SDLGame::instance()->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}

}
void EndState::goToMenuState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->popState();
	SDLGame::instance()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);
}

void EndState::resetLevel(AnimalCooking* ac)
{
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(SDLGame::instance()->getCurrentLevel(), ac));
	SDLGame::instance()->setMaxScore(0);
	SDLGame::instance()->setScore(0);
}

void EndState::createButtons()
{
	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();
	int winHeight = SDLGame::instance()->getWindowHeight();
	int winWidth = SDLGame::instance()->getWindowWidth();
	int nextLevelLimit = 50;
	int degrees = 7;

	//------------------>Volver al MapState<---------------------
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(138,
		winHeight - 128),
		Vector2D(),
		64,
		64,
		0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);
	ButtonBehaviour* bb = returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	ButtonRenderer* br = returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapIcon), nullptr);
	bb->setButtonRenderer(br);

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
	bb = ResetLevelButton->addComponent<ButtonBehaviour>(resetLevel, app);
	br = ResetLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ReplayIcon), nullptr);
	bb->setButtonRenderer(br);

	//------------------>Siguiente nivel<---------------------
	//Si el score es el suficiente para pasar al siguiente nivel
	if (score >= (double)(maxScore * nextLevelLimit / 100.0)) {

		if (SDLGame::instance()->getCurrentLevel() == SDLGame::instance()->getCurrenUnlockLevel()) {
			SDLGame::instance()->addCurrentUnlockLevel();
		}

		Entity* NextLevelButton = stage->addEntity();
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
		bb = NextLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
		br = NextLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::NextLevelIcon), nullptr);
		bb->setButtonRenderer(br);
		//Ponemos la m�sica de ganar
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::End_Win, 0);
	}
	else {
		//Ponemos la m�sica de perder
		SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::End_Lost, 0);
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
	bb = returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);
	br = returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIcon), nullptr);
	bb->setButtonRenderer(br);
	//-----------------------------------------------------------------------------------------

	//Final
	Entity* lv = stage->addEntity();
	lv->addComponent<LevelViewer>(500, 1000, 1500, nextLevelLimit, 75, 95,(double)(score)/maxScore);
	stage->addToGroup(lv, ecs::GroupID::ui);

	Entity* Player1Idle = stage->addEntity();
	Player1Idle->addComponent<Transform>(Vector2D(
		casillaX * 2,
		winHeight - casillaY * 5),
		Vector2D(),
		4 * casillaX,
		4 * casillaY,
		0);
	Animator* p1Anim = Player1Idle->addComponent<Animator>();
	Player1Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigAttack));
	stage->addToGroup(Player1Idle, ecs::GroupID::PlayerLayer);
	p1Anim->setCurrentState(Animator::States::Idle);

	Entity* Player2Idle = stage->addEntity();
	Player2Idle->addComponent<Transform>(Vector2D(
		casillaX * 6,
		winHeight - casillaY * 5),
		Vector2D(),
		4 * casillaX,
		4 * casillaY,
		0);
	Animator* p2Anim = Player2Idle->addComponent<Animator>();
	Player2Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenAttack));
	stage->addToGroup(Player2Idle, ecs::GroupID::PlayerLayer);
	p2Anim->setCurrentState(Animator::States::Idle);

}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);	
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 1), ac));
	SDLGame::instance()->setMaxScore(0);
	SDLGame::instance()->setScore(0);
}

void EndState::createPlayers()
{
	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();
	int winHeight = SDLGame::instance()->getWindowHeight();
	int winWidth = SDLGame::instance()->getWindowWidth();
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
		Player1Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigAttack));
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
		Player2Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenAttack));
		stage->addToGroup(Player2Idle, ecs::GroupID::PlayerLayer);
		p2Anim->setCurrentState(Animator::States::Idle);
	}
}

void EndState::draw()
{
	background->render(RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
	State::draw();
}
