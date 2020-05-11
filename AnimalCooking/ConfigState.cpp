#include "ConfigState.h"
#include "SDL_macros.h"
#include "MenuState.h"
#include "SDL.h"
#include "SliderRenderer.h"
#include "GPadController.h"

#include "GpadKeySwitcher.h"
#include "GpadKeySwitcherViewer.h"
#include "KeyboardKeySwitcher.h"
#include "KeyboardKeySwitcherViewer.h"

ConfigState::ConfigState(AnimalCooking* ac) :  State(ac), 
		game_(SDLGame::instance()), musicLastValue_(0.5), soundLastValue(0.5)
{
	cout << "Config State" << endl;
	initButtons();
	initSliders();
}

void ConfigState::update()
{
	State::update();
	double musicValue = sliderMusic_->getValue(), soundValue = sliderSound_->getValue();
	if (musicLastValue_ != musicValue) 
		game_->getAudioMngr()->setMusicVolume(game_->getOptions().volume.music_ = Uint8(musicValue * 128));
	else if (soundLastValue != soundValue) 
		game_->getAudioMngr()->setChannelVolume(game_->getOptions().volume.sounds_ = Uint8(soundValue * 128));
	
	musicLastValue_ = musicValue;
	soundLastValue = soundValue;
}

void ConfigState::initButtons()
{
	//Back button
	backButton_ = stage->addEntity();
	stage->addToGroup(backButton_, ecs::GroupID::ui);
	backButton_->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 3 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));
	
	//Toggle Window / Fullscreen
	Entity* resButton = stage->addEntity();
	stage->addToGroup(resButton, ecs::GroupID::ui);
	resButton->addComponent<Transform>(
		Vector2D((game_->getWindowWidth() / 3) - game_->getWindowWidth() / 10, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	resButton->addComponent<ButtonBehaviour>(resButtonCallback, app);
	resButton->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));
}

void ConfigState::initSliders()
{
	//Slider for Music
	Entity* sliderMusic = stage->addEntity();
	stage->addToGroup(sliderMusic, ecs::GroupID::ui);
	Transform* t = sliderMusic->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderMusic_ = sliderMusic->addComponent<SliderBehaviour>();
	sliderMusic->addComponent<SliderRenderer>();
	sliderMusic_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.music_ / 128.0);

	//Slider for Sound Effects
	Entity* sliderSound = stage->addEntity();
	stage->addToGroup(sliderSound, ecs::GroupID::ui);
	t = sliderSound->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 10, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderSound_ = sliderSound->addComponent<SliderBehaviour>();
	sliderSound->addComponent<SliderRenderer>();
	sliderSound_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.sounds_ / 128.0);

}

void ConfigState::initKeyModifiers()
{
	GPadController* gpCont = GPadController::instance();

	//Player1 Left
	Entity* e = stage->addEntity();
	stage->addToGroup(e, ecs::GroupID::ui);
	e->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 3 - game_->getWindowWidth() / 5, 5 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() * 2 / 5, game_->getWindowHeight() * 10 / 16, 0);
	if (gpCont->playerControllerConnected(0)) {
		e->addComponent<GpadKeySwitcher>(0);
		e->addComponent<GpadKeySwitcherViewer>();
	}
	else {
		e->addComponent<KeyboardKeySwitcher>(0, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		e->addComponent<KeyboardKeySwitcherViewer>();
	}

	//Player2 Right
	e = stage->addEntity();
	stage->addToGroup(e, ecs::GroupID::ui);
	e->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 5, 5 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() * 2 / 5, game_->getWindowHeight() * 10 / 16, 0);
	if (gpCont->playerControllerConnected(1)) {
		e->addComponent<GpadKeySwitcher>(1);
		e->addComponent<GpadKeySwitcherViewer>();
	}
	else {
		e->addComponent<KeyboardKeySwitcher>(1, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		e->addComponent<KeyboardKeySwitcherViewer>();
	}
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void ConfigState::resButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->toggleFullScreen();
}