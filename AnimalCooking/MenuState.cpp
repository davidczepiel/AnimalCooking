#include "MenuState.h"
#include "SDL_macros.h"

void MenuState::draw()
{
	background->render(backgroundRect);
	ruedecillaShadow->render(ruedecillaRect);
	ruedecilla->render(ruedecillaRect, ruedecillaAngle);
	State::draw();
}

void MenuState::leftState()
{
	switch (state) {
	case Credits:
		state = Config;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuConfigButton));
		break;
	case Play:
		state = Exit;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuExitButton));
		break;
	case Config:
		state = Play;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuPlayButton));
		break;
	case Exit:
		state = Credits;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuCreditsButton));
		break;
	}
	ruedecillaAngle -= 45.0;
}

void MenuState::rightState()
{
	switch (state) {
	case Exit:
		state = Play;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuPlayButton));
		break;
	case Play:
		state = Config;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuConfigButton));
		break;
	case Config:
		state = Credits;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuCreditsButton));
		break;
	case Credits:
		state = Exit;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuExitButton));
		break;
	}
	ruedecillaAngle += 45.0;
}

void MenuState::selectedState()
{
	switch (state) {
	case Credits:
		creditsMenuCallback();
		break;
	case Config:
		optionsMenuCallback();
		break;
	case Play:
		playMenuCallback();
		break;
	case Exit:
		closeGame();
		break;
	}
}

void MenuState::playMenuCallback() {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	 SDLGame::instance()->getFSM()->pushState(new MapState(app));
}

void MenuState::optionsMenuCallback() {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance() ->getFSM()->pushState(new ConfigState(app));
}

void MenuState::creditsMenuCallback() {
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->pushState(new CreditsState(app));
}

void MenuState::closeGame() {
	app->stop();
}

MenuState::MenuState(AnimalCooking* ac) : State(ac), state(SelectionState::Play), ruedecillaAngle(0.0) {

	SDLGame::instance()->getAudioMngr()->playMusic(Resources::AudioId::MenuInicio);

	

	double casillaX = SDLGame::instance()->getWindowWidth() / 16;
	double casillaY = SDLGame::instance()->getWindowHeight() / 9;
	SDLGame::instance()->setCasillaX(casillaX);
	SDLGame::instance()->setCasillaY(casillaY);

	backgroundRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	ruedecillaRect = RECT((SDLGame::instance()->getWindowWidth() * 850) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080, (SDLGame::instance()->getWindowWidth() * 192) / 1920, (SDLGame::instance()->getWindowWidth() * 195) / 1920);

	background = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuBackground);
	ruedecilla = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuRuedecilla);
	ruedecillaShadow = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuRuedecillaShadow);

	rightButton_ = stage->addEntity();
	leftButton_ = stage->addEntity();
	selectionButton_ = stage->addEntity();
	padNavigation_ = stage->addEntity();

	stage->addToGroup(rightButton_, ecs::GroupID::Layer1);
	stage->addToGroup(leftButton_, ecs::GroupID::Layer1);
	stage->addToGroup(selectionButton_, ecs::GroupID::Layer1);

	leftButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() * 650) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080), Vector2D(0, 0), (SDLGame::instance()->getWindowWidth() * 200.0) / 1920, (SDLGame::instance()->getWindowHeight() * 200.0) / 1080, 0);
	leftButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuArrow));
	leftButton_->addComponent<MenuButtonBehaviour>(this, MenuButtonBehaviour::ButtonType::LeftArrow);

	rightButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() * 1050) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080), Vector2D(0, 0), (SDLGame::instance()->getWindowWidth() * 200.0) / 1920, (SDLGame::instance()->getWindowHeight() * 200.0) / 1080, 0);
	rightButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuArrowR));
	rightButton_->addComponent<MenuButtonBehaviour>(this, MenuButtonBehaviour::ButtonType::RightArr);

	selectionButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() * 400) / 1920, (SDLGame::instance()->getWindowHeight() * 250) / 1080), Vector2D(0, 0), (SDLGame::instance()->getWindowWidth() * 1072.0) / 1920, (SDLGame::instance()->getWindowHeight() * 360.0) / 1080, 0);
	selectionButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuPlayButton));
	selectionButton_->addComponent<MenuButtonBehaviour>(this, MenuButtonBehaviour::ButtonType::SelectionButton);

	MainMenuPadNavigation* m = padNavigation_->addComponent<MainMenuPadNavigation>();
	m->setLeftArrow(leftButton_);
	m->setSelectButton(selectionButton_);
	m->setRightArrow(rightButton_);

	ifstream f;
	f.open("../AnimalCooking/resources/cfg/options.txt");
	if (f.is_open()) {
		float value;
		f >> value; 
		SDLGame::instance()->getAudioMngr()->setMusicVolume(SDLGame::instance()->getOptions().volume.music_ = Uint8(value * 128));
		f >> value;
		SDLGame::instance()->getAudioMngr()->setChannelVolume(SDLGame::instance()->getOptions().volume.sounds_ = Uint8(value * 128));

		bool v;
		f >> v; if (!v) SDLGame::instance()->toggleFullScreen();
		f >> v; SDLGame::instance()->getOptions().showKeyToPress = v;

		loadPlayer(f, 0, SDLGame::instance()->getOptions());
		loadPlayer(f, 1, SDLGame::instance()->getOptions());
	}
	f.close();
}

void MenuState::loadPlayer(ifstream& f, Uint8 player, config::Options& o)
{
	Sint32 aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].PICKUP = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].ATTACK = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].OPEN = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].PREVIOUS = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].NEXT = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].FINISHER = (SDL_Keycode)aux;

	aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].PICKUP = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].ATTACK = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].OPEN = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].PREVIOUS = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].NEXT = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].FINISHER = (SDL_GameControllerButton)aux;
}

MenuState::~MenuState()
{
}
