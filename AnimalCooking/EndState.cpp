#include "EndState.h"
#include "SDL_macros.h"
#include "LevelViewer.h"
#include "PlayerViewer.h"
#include "Transform.h"
#include "Animator.h"

EndState::EndState(AnimalCooking* ac,int score,int maxScore) :State(ac),score(score),maxScore(maxScore) {

	//Botones
	Entity* returnToMapButton = stage->addEntity();
	returnToMapButton->addComponent<Transform>(Vector2D(138,
		SDLGame::instance()->getWindowHeight() - 128), Vector2D(), 64, 64, 0);
	stage->addToGroup(returnToMapButton, ecs::GroupID::Layer1);
	int degrees = 7;
	returnToMapButton->addComponent<ButtonBehaviour>(goToMapState, app);
	returnToMapButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MapIcon), nullptr);
	Entity* NextLevelButton = stage->addEntity();
	stage->addToGroup(NextLevelButton, ecs::GroupID::Layer1);

	Entity* ResetLevelButton = stage->addEntity();
	stage->addToGroup(ResetLevelButton, ecs::GroupID::Layer1);
	ResetLevelButton->addComponent<Transform>(Vector2D(
		SDLGame::instance()->getWindowWidth() - 3.75 * SDLGame::instance()->getCasillaLength() +
		SDLGame::instance()->getCasillaLength() / 2,
		5 * SDLGame::instance()->getCasillaLength() - sin(degrees)),
		Vector2D(),
		SDLGame::instance()->getCasillaLength() / 2,
		SDLGame::instance()->getCasillaLength() / 2,
		degrees);
	ResetLevelButton->addComponent<ButtonBehaviour>(resetLevel, app);
	ResetLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ReplayIcon), nullptr);

	NextLevelButton->addComponent<Transform>(Vector2D
	(SDLGame::instance()->getWindowWidth() - 2.75 * SDLGame::instance()->getCasillaLength() +
		SDLGame::instance()->getCasillaLength() / 2,
		SDLGame::instance()->getWindowHeight() - 3.3 * SDLGame::instance()->getCasillaLength() -
		SDLGame::instance()->getCasillaLength() / 2 + sin(degrees)),
		Vector2D(),
		SDLGame::instance()->getCasillaLength() / 2,
		SDLGame::instance()->getCasillaLength() / 2,
		degrees);
	NextLevelButton->addComponent<ButtonBehaviour>(goToLoadState, app);
	NextLevelButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::NextLevelIcon), nullptr);

	Entity* returnToMenuButton = stage->addEntity();
	stage->addToGroup(returnToMenuButton, ecs::GroupID::Layer1);

	returnToMenuButton->addComponent<Transform>(Vector2D(64,

		SDLGame::instance()->getWindowHeight() - 128), Vector2D(), 64, 64, 0);
	returnToMenuButton->addComponent<ButtonBehaviour>(goToMenuState, app);

	returnToMenuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::HomeIcon), nullptr);
	//-----------------------------------------------------------------------------------------

	//Final
	score = 133;
	Entity* lv = stage->addEntity();
	lv->addComponent<LevelViewer>(500, 1000, 1500, 50, 75, 95,(double)(score)/maxScore);
	stage->addToGroup(lv, ecs::GroupID::ui);

	Entity* Player1Idle = stage->addEntity();
	Player1Idle->addComponent<Transform>(Vector2D(
		SDLGame::instance()->getCasillaLength() * 2,
		SDLGame::instance()->getWindowHeight() - SDLGame::instance()->getCasillaLength() * 5),
		Vector2D(),
		4 * SDLGame::instance()->getCasillaLength(),
		4 * SDLGame::instance()->getCasillaLength(),
		0);
	Animator* p1Anim = Player1Idle->addComponent<Animator>();
	Player1Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
	stage->addToGroup(Player1Idle, ecs::GroupID::PlayerLayer);
	p1Anim->setCurrentState(Animator::States::Idle);

	Entity* Player2Idle = stage->addEntity();
	Player2Idle->addComponent<Transform>(Vector2D(
		SDLGame::instance()->getCasillaLength() * 6,
		SDLGame::instance()->getWindowHeight() - SDLGame::instance()->getCasillaLength() * 5),
		Vector2D(),
		4 * SDLGame::instance()->getCasillaLength(),
		4 * SDLGame::instance()->getCasillaLength(),
		0);
	Animator* p2Anim = Player2Idle->addComponent<Animator>();
	Player2Idle->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pollo));
	stage->addToGroup(Player2Idle, ecs::GroupID::PlayerLayer);
	p2Anim->setCurrentState(Animator::States::Idle);

}
void EndState::goToLoadState(AnimalCooking* ac) {
	goToMapState(ac);
	SDLGame::instance()->getFSM()->pushState(new ScreenLoader(static_cast<Resources::Level> (SDLGame::instance()->getCurrentLevel() + 1), ac));
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

}
