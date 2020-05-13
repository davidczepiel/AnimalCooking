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
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuPlayButton));
		break;
	case Play:
		state = Options;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuConfigButton));
		break;
	case Options:
		state = Exit;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuExitButton));
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
		state = Options;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuConfigButton));
		break;
	case Credits:
		state = Exit;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuExitButton));
		break;
	case Options:
		state = Play;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuPlayButton));
		break;
	case Play:
		state = Credits;
		selectionButton_->getComponent<MenuButtonRenderer>(ecs::MenuButtonRenderer)->setTexture(SDLGame::instance()->getTextureMngr()->getTexture(Resources::MainMenuCreditsButton));
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
	SDLGame::instance()->getFSM()->pushState(new MapState(app));
}

void MenuState::optionsMenuCallback() {
	SDLGame::instance()->getFSM()->pushState(new ConfigState(app));
}

void MenuState::creditsMenuCallback() {
	SDLGame::instance()->getFSM()->pushState(new CreditsState(app));
}

void MenuState::closeGame() {
	app->stop();
}

MenuState::MenuState(AnimalCooking* ac) : State(ac), state(SelectionState::Play), ruedecillaAngle(0.0) {
	cout << "Menu State" << endl;

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
}

MenuState::~MenuState()
{
}
