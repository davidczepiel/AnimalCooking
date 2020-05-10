#include "ConfigState.h"
#include "SDL_macros.h"
#include "MenuState.h"
#include "SDL.h"
#include "SliderRenderer.h"

ConfigState::ConfigState(AnimalCooking* ac) :  State(ac), musicLastValue_(0.5), soundLastValue(0.5)
{
	cout << "Config State" << endl;
	game_ = SDLGame::instance();

	backButton_ = stage->addEntity();
	stage->addToGroup(backButton_, ecs::GroupID::ui);
	backButton_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10,0);
	backButton_->addComponent<ButtonBehaviour>(backButtonCallback, app);
	backButton_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), 
											  game_->getTextureMngr()->getTexture(Resources::Button));

	Entity* resButton2 = stage->addEntity();
	stage->addToGroup(resButton2, ecs::GroupID::ui);
	resButton2->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10, 
		4 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	resButton2->addComponent<ButtonBehaviour>(resButtonCallback, app);
	resButton2->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));

	Entity *sliderMusic = stage->addEntity();
	stage->addToGroup(sliderMusic, ecs::GroupID::ui);
	Transform* t = sliderMusic->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10,
		5 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	sliderMusic_ = sliderMusic->addComponent<SliderBehaviour>();
	sliderMusic->addComponent<SliderRenderer>();
	sliderMusic_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (SDLGame::instance()->getOptions().volume.music_ / 128.0);

	Entity* sliderSound = stage->addEntity();
	stage->addToGroup(sliderSound, ecs::GroupID::ui);
	t = sliderSound->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - game_->getWindowWidth() / 10,
		6 * game_->getWindowHeight() / 10),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 10, 0);
	sliderSound_ = sliderSound->addComponent<SliderBehaviour>();
	sliderSound->addComponent<SliderRenderer>();
	sliderSound_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (SDLGame::instance()->getOptions().volume.sounds_ / 128.0);
}

void ConfigState::update()
{
	State::update();
	double musicValue = sliderMusic_->getValue(), soundValue = sliderSound_->getValue();
	if (musicLastValue_ != musicValue) 
		SDLGame::instance()->getAudioMngr()->setMusicVolume(SDLGame::instance()->getOptions().volume.music_ = Uint8(musicValue * 128));
	else if (soundLastValue != soundValue) 
		SDLGame::instance()->getAudioMngr()->setChannelVolume(SDLGame::instance()->getOptions().volume.sounds_ = Uint8(soundValue * 128));
	
	musicLastValue_ = musicValue;
	soundLastValue = soundValue;
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