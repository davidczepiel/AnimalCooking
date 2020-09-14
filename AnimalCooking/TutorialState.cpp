#include "TutorialState.h"
#include "FSM.h"
#include "GPadController.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "ButtonPadNavigation.h"

TutorialState::TutorialState(AnimalCooking* ac): State(ac), 
	game_(SDLGame::instance()), 
	backGround_(game_->getTextureMngr()->getTexture(Resources::Config_Background))
{
//Manager
	Entity* imagesManagerEntity = stage->addEntity();
	stage->addToGroup(imagesManagerEntity, ecs::GroupID::Layer1);
	imagesManagerEntity->addComponent<Transform>(
		Vector2D(400, 250),
		Vector2D(), 1152, 648, 0);
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
	goLeftButton->addComponent<Transform>(Vector2D(250, (game_->getWindowHeight() / 2)), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = goLeftButton->addComponent<ButtonBehaviour>(moveLeft, app);
	br = goLeftButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonPrev), nullptr);
	bb->setButtonRenderer(br);

//Right
	Entity* goRightButton = stage->addEntity();
	stage->addToGroup(goRightButton, ecs::GroupID::topLayer);
	goRightButton->addComponent<Transform>(Vector2D(1570, game_->getWindowHeight() / 2), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = goRightButton->addComponent<ButtonBehaviour>(moveRight, app);
	br = goRightButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonNext), nullptr);
	bb->setButtonRenderer(br);

//Jump Buttons ------------------------------------------------------------------------------------------------------------------------------------------------------------------
	Entity* but1 = stage->addEntity();
	stage->addToGroup(but1, ecs::GroupID::topLayer);
	but1->addComponent<Transform>(Vector2D(800, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but1->addComponent<ButtonBehaviour>(goTo1, app);
	br = but1->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);

	Entity* but2 = stage->addEntity();
	stage->addToGroup(but2, ecs::GroupID::topLayer);
	but2->addComponent<Transform>(Vector2D(850, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but2->addComponent<ButtonBehaviour>(goTo2, app);
	br = but2->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);

	Entity* but3 = stage->addEntity();
	stage->addToGroup(but3, ecs::GroupID::topLayer);
	but3->addComponent<Transform>(Vector2D(900, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but3->addComponent<ButtonBehaviour>(goTo3, app);
	br = but3->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);

	Entity* but4 = stage->addEntity();
	stage->addToGroup(but4, ecs::GroupID::topLayer);
	but4->addComponent<Transform>(Vector2D(950, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but4->addComponent<ButtonBehaviour>(goTo4, app);
	br = but4->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);

	Entity* but5 = stage->addEntity();
	stage->addToGroup(but5, ecs::GroupID::topLayer);
	but5->addComponent<Transform>(Vector2D(1000, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but5->addComponent<ButtonBehaviour>(goTo5, app);
	br = but5->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);

	Entity* but6 = stage->addEntity();
	stage->addToGroup(but6, ecs::GroupID::topLayer);
	but6->addComponent<Transform>(Vector2D(1050, 1000), Vector2D(), aux->getWidth() - 60, aux->getHeight() + aux->getHeight() / 3);
	bb = but6->addComponent<ButtonBehaviour>(goTo6, app);
	br = but6->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::TextureId::MapRestaurantButton), nullptr);
	bb->setButtonRenderer(br);


//PadNavigation
	Entity* padNavigation = stage->addEntity();
	ButtonPadNavigation* bp = padNavigation->addComponent<ButtonPadNavigation>();
	bp->onlyListenTo(0);
	bp->AddButton(exitButton, nullptr, goLeftButton, goLeftButton, goRightButton);
	bp->AddButton(goLeftButton, exitButton, but1, nullptr, goRightButton);
	bp->AddButton(goRightButton, exitButton, but6, goLeftButton, nullptr);
	bp->AddButton(but1, goLeftButton, nullptr, but6, but2);
	bp->AddButton(but2, goLeftButton, nullptr, but1, but3);
	bp->AddButton(but3, goLeftButton, nullptr, but2, but4);
	bp->AddButton(but4, goRightButton, nullptr, but3, but5);
	bp->AddButton(but5, goRightButton, nullptr, but4, but6);
	bp->AddButton(but6, goRightButton, nullptr, but5, but1);
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

void TutorialState::goTo1(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}

void TutorialState::goTo2(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}

void TutorialState::goTo3(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}

void TutorialState::goTo4(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}

void TutorialState::goTo5(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}

void TutorialState::goTo6(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	static_cast<TutorialState*>(SDLGame::instance()->getFSM()->currentState())->getTutorialManager()->go(1);
}
