#include "PauseState.h"
#include "MenuState.h"
#include "PlayState.h"
//#include "ConfigState.h"

PauseState::PauseState(AnimalCooking* ac) : State(ac)
{

	SDLGame* game_ = SDLGame::instance();

	game_->getAudioMngr()->pauseMusic();
	game_->getAudioMngr()->pauseChannel(-1);

	int x = SDLGame::instance()->getWindowWidth() / 2;
	int y = SDLGame::instance()->getWindowHeight() / 5;
	int buttonHeight = 150;
	int buttonWidth = 400;
	resumeButton = stage->addEntity();
	resumeButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	ButtonBehaviour* bb = resumeButton->addComponent<ButtonBehaviour>(resumeCallback, app);
	resumeText_ = new Texture(game_->getRenderer(), "Resume", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0xffffffff) });
	ButtonRenderer* br = resumeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::botonPauseState), resumeText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(resumeButton, ecs::GroupID::Layer1);

	restartButton = stage->addEntity();
	restartButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 2 * y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = restartButton->addComponent<ButtonBehaviour>(restartCallback, app);
	restartText_ = new Texture(game_->getRenderer(), "Restart Level", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0xffffffff) });
	br = restartButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::botonPauseState), restartText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(restartButton, ecs::GroupID::Layer1);

	optionsButton = stage->addEntity();
	optionsButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 3 * y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = optionsButton->addComponent<ButtonBehaviour>(optionsCallback, app);
	optionsText_ = new Texture(game_->getRenderer(), "Options", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0xffffffff) });
	br = optionsButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::botonPauseState), optionsText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(optionsButton, ecs::GroupID::Layer1);

	closeButton = stage->addEntity();
	closeButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 4 * y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = closeButton->addComponent<ButtonBehaviour>(closeCallback, app);
	closeText_ = new Texture(game_->getRenderer(), "Leave level", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0xffffffff) });
	br = closeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::botonPauseState), closeText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(closeButton, ecs::GroupID::Layer1);

	padNavigation = stage->addEntity();
	ButtonPadNavigation* b = padNavigation->addComponent<ButtonPadNavigation>();
	b->AddButton(resumeButton, closeButton, restartButton, nullptr, nullptr);
	b->AddButton(restartButton, resumeButton, optionsButton, nullptr, nullptr);
	b->AddButton(optionsButton, restartButton, closeButton, nullptr, nullptr);
	b->AddButton(closeButton, optionsButton, resumeButton, nullptr, nullptr);

}

PauseState::~PauseState()
{
	delete resumeText_; resumeText_ = nullptr;
	delete restartText_; restartText_ = nullptr;
	delete optionsText_; optionsText_ = nullptr;
	delete closeText_; closeText_ = nullptr;
}

void PauseState::draw()
{
	SDLGame::instance()->getTextureMngr()->getTexture(Resources::pauseStateBackground)->render(RECT(0,0,SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight()));
	State::draw();
}

void PauseState::update()
{

		GPadController* gpad = GPadController::instance();
		if ((gpad->playerControllerConnected(0) || gpad->playerControllerConnected(1)) && gpad->isAnyButtonJustPressed()) {

			if ((gpad->playerPressed(0, SDL_CONTROLLER_BUTTON_B) || gpad->playerPressed(1, SDL_CONTROLLER_BUTTON_B))) {
				resumeCallback(getAnimalCooking());
			}
		}
		State::update();
}

void PauseState::optionsCallback(AnimalCooking* ac)
{
	SDLGame* game = SDLGame::instance();
	game->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + game->getRandGen()->nextInt(0, 6), 0);
	game->getFSM()->pushState(new ConfigState(ac));
}

void PauseState::restartCallback(AnimalCooking* ac)
{
	SDLGame* game = SDLGame::instance();

	FSM* fsm = game->getFSM(); //Ir al map state
	fsm->popState();
	fsm->popState();

	game->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + game->getRandGen()->nextInt(0, 6), 0);
	game->getFSM()->pushState(new ScreenLoader(game->getCurrentLevel() + 2, ac)); //Seleccionar el nivel adecuado
}

void PauseState::resumeCallback(AnimalCooking* ac)
{
	SDLGame* game = SDLGame::instance();
	game->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + game->getRandGen()->nextInt(0, 6), 0);
	game->getFSM()->popState([]() {
			static_cast<PlayState*>(SDLGame::instance()->getFSM()->currentState())->resumeTimers();
			SDLGame::instance()->getAudioMngr()->resumeMusic();
			SDLGame::instance()->getAudioMngr()->resumeChannel(-1);
		});
}

void PauseState::closeCallback(AnimalCooking* ac)
{
	SDLGame* game = SDLGame::instance();
	FSM* fsm = game->getFSM();

	fsm->popState();
	fsm->popState();

	game->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + game->getRandGen()->nextInt(0, 6), 0);
	game->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);
}

