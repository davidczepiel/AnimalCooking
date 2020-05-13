#include "PauseState.h"
#include "MenuState.h"
#include "PlayState.h"
//#include "ConfigState.h"

PauseState::PauseState(AnimalCooking* ac) : State(ac)
{
	cout << "PauseState";

	SDLGame* game_ = SDLGame::instance();

	game_->getAudioMngr()->pauseMusic();
	game_->getAudioMngr()->pauseChannel(-1);

	int x = SDLGame::instance()->getWindowWidth()/2;
	int y = SDLGame::instance()->getWindowHeight()/5;
	int buttonHeight = 100;
	int buttonWidth = 180;
	resumeButton = stage->addEntity();
	resumeButton->addComponent<Transform>(Vector2D(x-(buttonWidth/2), y-(buttonHeight/2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	ButtonBehaviour* bb = resumeButton->addComponent<ButtonBehaviour>(resumeCallback, app);
	resumeText_ = new Texture(game_->getRenderer(), "Resume", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
	ButtonRenderer* br = resumeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), resumeText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(resumeButton, ecs::GroupID::Layer1);

	configButton = stage->addEntity();
	configButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 2*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = configButton->addComponent<ButtonBehaviour>(configCallback, app);
	optionsText_ = new Texture(game_->getRenderer(), "Options", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
	br =configButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), optionsText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(configButton, ecs::GroupID::Layer1);

	menuButton = stage->addEntity();
	menuButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 3*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = menuButton->addComponent<ButtonBehaviour>(menuCallback, app);
	menuText_ = new Texture(game_->getRenderer(), "Menu", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
	br = menuButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), menuText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(menuButton, ecs::GroupID::Layer1);

	closeButton = stage->addEntity();
	closeButton->addComponent<Transform>(Vector2D(x - (buttonWidth / 2), 4*y - (buttonHeight / 2)), Vector2D(0, 0), buttonWidth, buttonHeight, 0);
	bb = closeButton->addComponent<ButtonBehaviour>(closeCallback, app);
	closeText_ = new Texture(game_->getRenderer(), "Exit", (game_->getFontMngr()->getFont(Resources::QuarkCheese70)), { COLOR(0x000000ff) });
	br = closeButton->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), closeText_);
	bb->setButtonRenderer(br);
	stage->addToGroup(closeButton, ecs::GroupID::Layer1);

	padNavigation = stage->addEntity();
	ButtonPadNavigation* b =padNavigation->addComponent<ButtonPadNavigation>();
	b->AddButton(resumeButton,nullptr,configButton,nullptr,nullptr);
	b->AddButton(configButton,resumeButton,menuButton,nullptr,nullptr);
	b->AddButton(menuButton, configButton, closeButton, nullptr, nullptr);
	b->AddButton(closeButton, menuButton, nullptr, nullptr, nullptr);
	if ((GPadController::instance()->playerControllerConnected(0) || GPadController::instance()->playerControllerConnected(1)))
		GETCMP2(resumeButton, ButtonBehaviour)->setFocusByController(true);
}

PauseState::~PauseState()
{
	delete resumeText_; resumeText_ = nullptr;
	delete optionsText_; optionsText_ = nullptr;
	delete menuText_; menuText_ = nullptr;
	delete closeText_; closeText_ = nullptr;
}

void PauseState::menuCallback(AnimalCooking* ac)
{
	cout << "Menu";
	FSM* fsm= SDLGame::instance()->getFSM();
	for (int i = 0; i < 3; i++)
	{
		fsm->popState();
	}
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);
}

void PauseState::configCallback(AnimalCooking* ac)
{
	cout << "Config";
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->pushState(new ConfigState(ac));
}

void PauseState::resumeCallback(AnimalCooking* ac)
{
	cout << "Resume";
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState([]() { 
			static_cast<PlayState*>(SDLGame::instance()->getFSM()->currentState())->resumeTimers();
			SDLGame::instance()->getAudioMngr()->resumeMusic();
			SDLGame::instance()->getAudioMngr()->resumeChannel(-1);
		});
}

void PauseState::closeCallback(AnimalCooking* ac)
{
	ac->stop();
}

