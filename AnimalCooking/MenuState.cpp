#include "MenuState.h"
#include "SDL_macros.h"

void MenuState::draw()
{
	background->render(backgroundRect);
	ruedecilla->render(ruedecillaRect);
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
		state = Credits;
		break;
	}
}

void MenuState::rightState()
{
	switch (state) {
	case Credits:
		state = Options;
		break;
	case Options:
		state = Play;
		break;
	case Play:
		state = Credits;
		break;
	}
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
	 SDLGame::instance()->getFSM()->pushState(new MapState());
}

void MenuState::optionsMenuCallback() {
	SDLGame::instance() ->getFSM()->pushState(new ConfigState());
}

void MenuState::creditsMenuCallback() {
	SDLGame::instance()->getFSM()->pushState(new CreditsState());
}

MenuState::MenuState() : State(), state(SelectionState::Play) {
	cout << "Menu State" << endl;
	backgroundRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	//ruedecillaRect = RECT()        <------ a ojo ¿?
	//background = SDLGame::instance()->getTextureMngr()->getTexture();
	//ruedecilla = SDLGame::instance()->getTextureMngr()->getTexture();

	rightButton_ = stage->addEntity();
	leftButton_ = stage->addEntity();

	stage->addToGroup(rightButton_, ecs::GroupID::Layer1);
	stage->addToGroup(leftButton_, ecs::GroupID::Layer1);

	rightButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() / 4) * 2, (SDLGame::instance()->getWindowHeight() / 4) * 3), Vector2D(0, 0), 100.0, 100.0, 0);
	rightButton_->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button),nullptr);
	rightButton_->addComponent<ButtonBehaviour>(rightButton_);

	leftButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() / 4) * 3, (SDLGame::instance()->getWindowHeight() / 4) * 3), Vector2D(0, 0), 100.0, 100.0, 0);
	leftButton_->addComponent<ButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button), nullptr);
	leftButton_->addComponent<ButtonBehaviour>(leftButton_);
}

MenuState::~MenuState()
{
	delete rightButton_;
	delete leftButton_;
}




