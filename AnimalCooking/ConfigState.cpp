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

#include "ButtonPadNavigation.h"

ConfigState::ConfigState(AnimalCooking* ac) :  State(ac), 
		game_(SDLGame::instance()), musicLastValue_(0.5), soundLastValue(0.5)
{
	cout << "Config State" << endl;
	initButtons();
	initSliders();
	initKeyModifiers();
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
	salir = stage->addEntity();
	stage->addToGroup(salir, ecs::GroupID::ui);
	salir->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 3 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	ButtonBehaviour* bb = salir->addComponent<ButtonBehaviour>(backButtonCallback, app);
	ButtonRenderer* br = salir->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Back));
	bb->setButtonRenderer(br);

	//Toggle Window / Fullscreen
	res = stage->addEntity();
	stage->addToGroup(res, ecs::GroupID::ui);
	res->addComponent<Transform>(
		Vector2D((game_->getWindowWidth() / 3) - game_->getWindowWidth() / 10, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	bb = res->addComponent<ButtonBehaviour>(resButtonCallback, app);
	br = res->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::ToggleFullscreen));
	bb->setButtonRenderer(br);
}

void ConfigState::initSliders()
{
	//Slider for Music
	sliderTop = stage->addEntity();
	stage->addToGroup(sliderTop, ecs::GroupID::ui);
	Transform* t = sliderTop->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderMusic_ = sliderTop->addComponent<SliderBehaviour>();
	sliderTop->addComponent<SliderRenderer>();
	sliderMusic_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.music_ / 128.0);

	//Slider for Sound Effects
	sliderBot = stage->addEntity();
	stage->addToGroup(sliderBot, ecs::GroupID::ui);
	t = sliderBot->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 10, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderSound_ = sliderBot->addComponent<SliderBehaviour>();
	sliderBot->addComponent<SliderRenderer>();
	sliderSound_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.sounds_ / 128.0);

}

void ConfigState::initKeyModifiers()
{
	GPadController* gpCont = GPadController::instance();

	bool insertPadNav = false;
	ButtonPadNavigation* bp = nullptr;
	//Player1 Left
	changeP1 = stage->addEntity();
	stage->addToGroup(changeP1, ecs::GroupID::ui);
	changeP1->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 3 - game_->getWindowWidth() / 5, 5 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() * 2 / 5, game_->getWindowHeight() * 10 / 16, 0);
	if (gpCont->playerControllerConnected(0)) {
		changeP1->addComponent<GpadKeySwitcher>(0, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		changeP1->addComponent<GpadKeySwitcherViewer>();
		
		Entity* e = stage->addEntity();
		bp = e->addComponent<ButtonPadNavigation>();
		bp->AddButton(salir, nullptr, res, nullptr, sliderTop);
		bp->AddButton(res, salir, changeP1, nullptr, sliderBot);
		bp->AddButton(sliderTop, nullptr, sliderBot, salir, nullptr, true);
	}
	else {
		changeP1->addComponent<KeyboardKeySwitcher>(0, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		changeP1->addComponent<KeyboardKeySwitcherViewer>();
	}
	
	//Player2 Right
	changeP2 = stage->addEntity();
	stage->addToGroup(changeP2, ecs::GroupID::ui);
	changeP2->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 3 - game_->getWindowWidth() / 5, 5 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() * 2 / 5, game_->getWindowHeight() * 10 / 16, 0);
	if (gpCont->playerControllerConnected(1)) {
		changeP2->addComponent<GpadKeySwitcher>(1, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		changeP2->addComponent<GpadKeySwitcherViewer>();

		bp->AddButton(sliderBot, sliderTop, changeP2, res, nullptr, true);
		bp->AddButton(changeP1, res, nullptr, nullptr, changeP2, true);
		bp->AddButton(changeP2, sliderBot, nullptr, changeP1, nullptr, true);
		insertPadNav = true;
	}
	else {
		changeP2->addComponent<KeyboardKeySwitcher>(1, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		changeP2->addComponent<KeyboardKeySwitcherViewer>();
	}

	if (!insertPadNav && bp) {
		bp->AddButton(sliderBot, sliderTop, changeP1, res, nullptr, true);
		bp->AddButton(changeP1, res, nullptr, nullptr, nullptr, true);
	}
	
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void ConfigState::resButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->toggleFullScreen();
}