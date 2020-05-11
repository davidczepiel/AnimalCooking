#include "EndState.h"
#include "SDL_macros.h"
#include "LevelViewer.h"
#include "PlayerViewer.h"
#include "Transform.h"
#include "Animator.h"

EndState::EndState(AnimalCooking* ac) :State(ac),score(0),maxScore(SDLGame::instance()->getMaxScore()) {
	score=SDLGame::instance()->getScore();
	
	double casillaX = SDLGame::instance()->getCasillaX();
	double casillaY = SDLGame::instance()->getCasillaY();
	int winHeight = SDLGame::instance()->getWindowHeight();
	int winWidth = SDLGame::instance()->getWindowWidth();
	int degrees = 7;
	int nextLevelLimit = 50;
	
	//Botones
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(138,
		winHeight - 128), 
		Vector2D(), 
		64, 
		64, 
		0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);
	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapIcon), nullptr);
	
	Entity* ResetLevelButton = stage->addEntity();
	stage->addToGroup(ResetLevelButton, ecs::GroupID::Layer1);
	ResetLevelButton->addComponent<Transform>(Vector2D(
		winWidth - 3.75 * casillaX +
		casillaX / 2,
		5 * casillaY - sin(degrees)),
		Vector2D(),
		casillaX / 2,
		casillaY / 2,
		degrees);
	ResetLevelButton->addComponent<ButtonBehaviour>(resetLevel, app);
	ResetLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ReplayIcon), nullptr);

	if (score >= (double)(maxScore * nextLevelLimit / 100.0)) {
		Entity* NextLevelButton = stage->addEntity();
		stage->addToGroup(NextLevelButton, ecs::GroupID::Layer1);
		NextLevelButton->addComponent<Transform>(Vector2D
		(winWidth - 2.75 * casillaX +
			casillaX / 2,
			winHeight - 3.3 * casillaY -
			casillaY / 2 + sin(degrees)),
			Vector2D(),
			casillaX / 2,
			casillaY / 2,
			degrees);
		NextLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
		NextLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::NextLevelIcon), nullptr);
	}
	Entity* returnToMenuButton = stage->addEntity();
	stage->addToGroup(returnToMenuButton, ecs::GroupID::Layer1);

	returnToMenuButton->addComponent<Transform>(Vector2D(64,
		winHeight - 128), 
		Vector2D(), 
		64, 
		64, 
		0);
	returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);

	returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIcon), nullptr);
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
	Player1Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
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
	Player2Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pollo));
	stage->addToGroup(Player2Idle, ecs::GroupID::PlayerLayer);
	p2Anim->setCurrentState(Animator::States::Idle);

}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 1), ac));
	SDLGame::instance()->setMaxScore(0);
	SDLGame::instance()->setScore(0);
}
void EndState::goToMapState(AnimalCooking* ac) {
	FSM* fsm = SDLGame::instance()->getFSM();
	for (int i = 0; i < 2; i++)
	{
		fsm->popState();
	}

}
void EndState::goToMenuState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->popState();
}

void EndState::resetLevel(AnimalCooking* ac)
{
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(SDLGame::instance()->getCurrentLevel(), ac));
	SDLGame::instance()->setMaxScore(0);
	SDLGame::instance()->setScore(0);
}
