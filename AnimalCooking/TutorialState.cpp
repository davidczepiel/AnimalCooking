#include "TutorialState.h"
#include "FSM.h"
#include "GPadController.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ButtonPadNavigation.h"


TutorialState::TutorialState(AnimalCooking* ac): State(ac), 
	game_(SDLGame::instance()), 
	backGround_(SDLGame::instance()->getTextureMngr()->getTexture(Resources::pauseStateBackground))
{
//Manager
	Entity* imagesManagerEntity = stage->addEntity();
	stage->addToGroup(imagesManagerEntity, ecs::GroupID::Layer1);
	imagesManagerEntity->addComponent<Transform>(
		Vector2D(108, 192),
		Vector2D(), 864, 1536, 0);
	tutorialManager = imagesManagerEntity->addComponent<TutorialManager>();

//Exit
	Entity* exitButton = stage->addEntity();
	stage->addToGroup(exitButton, ecs::GroupID::topLayer);
	exitButton->addComponent<Transform>(
		Vector2D(90, 120),
		Vector2D(), 275, 235, 0);
	ButtonBehaviour* bb = exitButton->addComponent<ButtonBehaviour>(GoBackMenu, app);
	ButtonRenderer* br = exitButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Config_BackButton), nullptr);
	bb->setButtonRenderer(br);

//Left
	Entity* goLeftButton = stage->addEntity();
	stage->addToGroup(goLeftButton, ecs::GroupID::topLayer);
	Texture* aux = game_->getTextureMngr()->getTexture(Resources::ButtonNext);
	goLeftButton->addComponent<Transform>(Vector2D(30, (game_->getWindowHeight() / 2)), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = goLeftButton->addComponent<ButtonBehaviour>(moveLeft, app);
	br = goLeftButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonNext), nullptr);
	bb->setButtonRenderer(br);

//Right
	Entity* goRightButton = stage->addEntity();
	stage->addToGroup(goRightButton, ecs::GroupID::topLayer);
	goRightButton->addComponent<Transform>(Vector2D(game_->getWindowWidth() - aux->getWidth(), (game_->getWindowHeight() / 2)), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = goRightButton->addComponent<ButtonBehaviour>(moveRight, app);
	br = goRightButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonPrev), nullptr);
	bb->setButtonRenderer(br);

//PadNavigation
	Entity* padNavigation = stage->addEntity();
	ButtonPadNavigation* bp = padNavigation->addComponent<ButtonPadNavigation>();
	bp->onlyListenTo(0);
	bp->AddButton(exitButton, nullptr, goLeftButton, nullptr, nullptr);
	bp->AddButton(goLeftButton, exitButton, nullptr, nullptr, goRightButton);
	bp->AddButton(goRightButton, exitButton, nullptr, goLeftButton, nullptr);
}

void TutorialState::update()
{
	GPadController* gpad = GPadController::instance();
	if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->isAnyButtonJustPressed()) {

		if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_B) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_B))) {
			GoBackMenu(app);
		}
	}
	if (InputHandler::instance()->isKeyDown(SDL_Scancode::SDL_SCANCODE_ESCAPE)) {
		GoBackMenu(app);
	}
	State::update();
}

void TutorialState::draw()
{
	backGround_->render(RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight()));
	State::draw();
}

void TutorialState::GoBackMenu(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void TutorialState::moveLeft(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->goLeft();
}

void TutorialState::moveRight(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->goRight();
}
