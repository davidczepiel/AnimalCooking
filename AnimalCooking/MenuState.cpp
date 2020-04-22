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
		state = Play;
		break;
	case Play:
		state = Options;
		break;
	case Options:
		state = Exit;
		break;
	case Exit:
		state = Credits;
		break;
	}
	ruedecillaAngle -= 45.0;
}

void MenuState::rightState()
{
	switch (state) {
	case Exit:
		state = Options;
		break;
	case Credits:
		state = Exit;
		break;
	case Options:
		state = Play;
		break;
	case Play:
		state = Credits;
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
	case Options:
		playMenuCallback();
		break;
	case Play:
		optionsMenuCallback();
		break;
	}
}

void MenuState::playMenuCallback() {
	 SDLGame::instance()->getFSM()->pushState(new MapState(app));
}

void MenuState::optionsMenuCallback() {
	SDLGame::instance() ->getFSM()->pushState(new ConfigState(app));
}

void MenuState::creditsMenuCallback() {
	SDLGame::instance()->getFSM()->pushState(new CreditsState(app));
}

void MenuState::closeGame() {
	app->stop();
}

MenuState::MenuState(AnimalCooking* ac) : State(ac), state(SelectionState::Play) {
	cout << "Menu State" << endl;
	backgroundRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	ruedecillaRect = RECT((SDLGame::instance()->getWindowWidth() * 850) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080, (SDLGame::instance()->getWindowWidth() * 192) / 1920, (SDLGame::instance()->getWindowWidth() * 195) / 1920);
	ruedecillaAngle = 0.0;

	background = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuBackground);
	ruedecilla = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuRuedecilla);
	ruedecillaShadow = SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuRuedecillaShadow);

	rightButton_ = stage->addEntity();
	leftButton_ = stage->addEntity();

	stage->addToGroup(rightButton_, ecs::GroupID::Layer1);
	stage->addToGroup(leftButton_, ecs::GroupID::Layer1);

	leftButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() * 650) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080), Vector2D(0, 0), 100.0, 100.0, 0);
	leftButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuArrow));
	leftButton_->addComponent<MenuButtonBehaviour>(this, false);

	rightButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() * 1050) / 1920, (SDLGame::instance()->getWindowHeight() * 923) / 1080), Vector2D(0, 0), 100.0, 100.0, 0);
	rightButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuArrowR));
	rightButton_->addComponent<MenuButtonBehaviour>(this, true);
}

MenuState::~MenuState()
{
	delete rightButton_;
	delete leftButton_;
}
