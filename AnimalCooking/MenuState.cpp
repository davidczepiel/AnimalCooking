#include "MenuState.h"
#include "SDL_macros.h"

void MenuState::draw()
{
	//background->render(backgroundRect);
	//ruedecilla->render(ruedecillaRect);
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

void MenuState::optionsMenuCallback(AnimalCooking* ac) {
	SDLGame::instance() ->getFSM()->pushState(new ConfigState(ac));
}

void MenuState::creditsMenuCallback(AnimalCooking* ac) {
	SDLGame::instance()->getFSM()->pushState(new CreditsState(ac));
}

MenuState::MenuState() : State(), state(SelectionState::Play) {
	cout << "Menu State" << endl;
	backgroundRect = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	//ruedecillaRect = RECT()        <------ a ojo �?
	background = SDLGame::instance()->getTextureMngr()->getTexture(Resources::SliderBackground);
	//ruedecilla = SDLGame::instance()->getTextureMngr()->getTexture();

	rightButton_ = stage->addEntity();
	leftButton_ = stage->addEntity();

	stage->addToGroup(rightButton_, ecs::GroupID::Layer1);
	stage->addToGroup(leftButton_, ecs::GroupID::Layer1);

	leftButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() / 4) * 2, (SDLGame::instance()->getWindowHeight() / 4) * 3), Vector2D(0, 0), 100.0, 100.0, 0);
	leftButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	leftButton_->addComponent<MenuButtonBehaviour>(this, false);

	rightButton_->addComponent<Transform>(Vector2D((SDLGame::instance()->getWindowWidth() / 4) * 3, (SDLGame::instance()->getWindowHeight() / 4) * 3), Vector2D(0, 0), 100.0, 100.0, 0);
	rightButton_->addComponent<MenuButtonRenderer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Button));
	rightButton_->addComponent<MenuButtonBehaviour>(this, true);
}

MenuState::~MenuState()
{
	delete rightButton_;
	delete leftButton_;
}




	exitButtonTr_ = exitButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2, (game_->getWindowHeight() / 4) * 3), Vector2D(0, 0), 200.0, 100, 0);
	exitButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);
	exitButton_->addComponent<ButtonBehaviour>(closeGame, app);
}
