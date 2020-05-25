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
#include "ImageViewer.h"
#include "ButtonChangeOnClick.h"


ConfigState::ConfigState(AnimalCooking* ac) :  State(ac), textSliderMusic(nullptr), textSliderSound(nullptr),
		game_(SDLGame::instance()), musicLastValue_(0.5), soundLastValue(0.5)
{
	cout << "Config State" << endl;
	initSliders();
	loadFromFile();
	initButtons();
	initKeyModifiers();
}

ConfigState::~ConfigState()
{
	saveToFile();
	delete textSliderMusic;
	delete textSliderSound;
}

void ConfigState::saveToFile()
{
	config::Options& o = game_->getOptions();
	ofstream f;
	f.open("../AnimalCooking/resources/cfg/options.txt");
	if (f.is_open()) {
		savePlayer(f, 0, o);
		savePlayer(f, 1, o);
		saveVolumeSetting(f);
	}
	f.close();
}

void ConfigState::loadFromFile()
{
	config::Options& o = game_->getOptions();
	ifstream f;
	f.open("../AnimalCooking/resources/cfg/options.txt");
	if (f.is_open()) {
		loadPlayer(f, 0, o);
		loadPlayer(f, 1, o);
		loadVolumeSetting(f);
	}
	f.close();
}

void ConfigState::savePlayer(ofstream& f, Uint8 player, const config::Options& o)
{
	f << (Sint32)o.players_keyboardKeys[player].PICKUP << " " << (Sint32)o.players_keyboardKeys[player].ATTACK << " "
	<< (Sint32)o.players_keyboardKeys[player].OPEN << " " << (Sint32)o.players_keyboardKeys[player].PREVIOUS << " "
	<< (Sint32)o.players_keyboardKeys[player].NEXT << " " << (Sint32)o.players_keyboardKeys[player].FINISHER << " " << endl;

	f << (Sint32)o.players_gPadButtons[player].PICKUP << " " << (Sint32)o.players_gPadButtons[player].ATTACK << " "
	<< (Sint32)o.players_gPadButtons[player].OPEN << " " << (Sint32)o.players_gPadButtons[player].PREVIOUS << " "
	<< (Sint32)o.players_gPadButtons[player].NEXT << " " << (Sint32)o.players_gPadButtons[player].FINISHER << " " << endl;
}

void ConfigState::saveVolumeSetting(ofstream& f)
{
	f << sliderMusic_->getValue() << " " << sliderSound_->getValue() << endl;
}

void ConfigState::loadPlayer(ifstream& f, Uint8 player, config::Options& o)
{
	Sint32 aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].PICKUP = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].ATTACK = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].OPEN = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].PREVIOUS = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].NEXT = (SDL_Keycode)aux;
	f >> aux; if (!f.fail()) o.players_keyboardKeys[player].FINISHER = (SDL_Keycode)aux;

	aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].PICKUP = (SDL_GameControllerButton)aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].ATTACK = (SDL_GameControllerButton)aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].OPEN = (SDL_GameControllerButton)aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].PREVIOUS = (SDL_GameControllerButton)aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].NEXT = (SDL_GameControllerButton)aux;
	f >> aux; if(!f.fail()) o.players_gPadButtons[player].FINISHER = (SDL_GameControllerButton)aux;
}

void ConfigState::loadVolumeSetting(ifstream& f)
{
	float value;
	f >> value; sliderMusic_->movePercentage(value);
	f >> value; sliderSound_->movePercentage(value);
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

void ConfigState::draw()
{
	SDL_Rect d = RECT(0, 0, SDLGame::instance()->getWindowWidth(), SDLGame::instance()->getWindowHeight());
	SDLGame::instance()->getTextureMngr()->getTexture(Resources::ConfigBackground)->render(d);
	State::draw();
}


void ConfigState::initButtons()
{
	//Back button
	salir = stage->addEntity();
	stage->addToGroup(salir, ecs::GroupID::ui);
	salir->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 5 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	ButtonBehaviour* bb = salir->addComponent<ButtonBehaviour>(backButtonCallback, app);
	ButtonRenderer* br = salir->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig),
		game_->getTextureMngr()->getTexture(Resources::Back));
	bb->setButtonRenderer(br);

	//Toggle Window / Fullscreen
	res = stage->addEntity();
	stage->addToGroup(res, ecs::GroupID::ui);
	res->addComponent<Transform>(
		Vector2D((game_->getWindowWidth() * 2 / 5) - game_->getWindowWidth() / 10, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	bb = res->addComponent<ButtonBehaviour>(resButtonCallback, app);
	res->addComponent<ButtonChangeOnClick>(SDLGame::instance()->getIfFullscreen());
	br = res->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig),
		game_->getTextureMngr()->getTexture(Resources::ToggleFullscreen));
	bb->setButtonRenderer(br);

	//Helper button
	helper = stage->addEntity();
	stage->addToGroup(helper, ecs::GroupID::ui);
	helper->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 2 / 5 - game_->getWindowWidth() / 10, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	bb = helper->addComponent<ButtonBehaviour>(helperButtonCallback, app);
	helper->addComponent<ButtonChangeOnClick>(SDLGame::instance()->getOptions().showKeyToPress);
	br = helper->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::ButtonConfig),
		game_->getTextureMngr()->getTexture(Resources::ToggleHelper));
	bb->setButtonRenderer(br);
	
}

void ConfigState::initSliders()
{
	//Slider for Music
	sliderTop = stage->addEntity();
	stage->addToGroup(sliderTop, ecs::GroupID::ui);
	Transform* t = sliderTop->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 3 / 5 - game_->getWindowWidth() / 20, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderMusic_ = sliderTop->addComponent<SliderBehaviour>();
	sliderTop->addComponent<SliderRenderer>();
	sliderMusic_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.music_ / 128.0);

	//Slider for Sound Effects
	sliderBot = stage->addEntity();
	stage->addToGroup(sliderBot, ecs::GroupID::ui);
	t = sliderBot->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 3 / 5 - game_->getWindowWidth() / 20, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 5, game_->getWindowHeight() / 16, 0);
	sliderSound_ = sliderBot->addComponent<SliderBehaviour>();
	sliderBot->addComponent<SliderRenderer>();
	sliderSound_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.sounds_ / 128.0);

	textSliderMusic = new Texture(game_->getRenderer(), "Music Volume", game_->getFontMngr()->getFont(Resources::QuarkCheese100), { COLOR(0xFFFFFFff) });
	textSliderSound = new Texture(game_->getRenderer(), "Sound Volume", game_->getFontMngr()->getFont(Resources::QuarkCheese100), { COLOR(0xFFFFFFff) });

	Entity* sliderText1 = stage->addEntity();
	stage->addToGroup(sliderText1, ecs::GroupID::ui);
	sliderText1->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 3.85 / 5, game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 6, game_->getWindowHeight() / 16, 0);
	sliderText1->addComponent<ImageViewer>(textSliderMusic);

	Entity* sliderText2 = stage->addEntity();
	stage->addToGroup(sliderText2, ecs::GroupID::ui);
	sliderText2->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() * 3.85 / 5, 3 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() / 6, game_->getWindowHeight() / 16, 0);
	sliderText2->addComponent<ImageViewer>(textSliderSound);
}

void ConfigState::initKeyModifiers()
{
	GPadController* gpCont = GPadController::instance();

	//Player1 Left
	changeP1 = stage->addEntity();
	stage->addToGroup(changeP1, ecs::GroupID::ui);
	changeP1->addComponent<Transform>(
		Vector2D(game_->getWindowWidth() / 3 - game_->getWindowWidth() / 5, 5 * game_->getWindowHeight() / 16),
		Vector2D(), game_->getWindowWidth() * 2 / 5, game_->getWindowHeight() * 10 / 16, 0);
	if (gpCont->playerControllerConnected(0)) {
		changeP1->addComponent<GpadKeySwitcher>(0, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16, false);
		changeP1->addComponent<GpadKeySwitcherViewer>();
		
		Entity* e = stage->addEntity();
		ButtonPadNavigation* bp = e->addComponent<ButtonPadNavigation>();
		bp->onlyListenTo(0);
		bp->AddButton(salir, nullptr, changeP1, sliderTop, helper);
		bp->AddButton(res, helper, changeP1, sliderBot, sliderBot);
		bp->AddButton(helper, nullptr, res, salir, sliderTop);
		bp->AddButton(sliderTop, nullptr, sliderBot, helper, salir, true);
		bp->AddButton(sliderBot, sliderTop, changeP1, res, res, true);
		bp->AddButton(changeP1, res, nullptr, nullptr, nullptr, true);
		GETCMP2(salir, ButtonBehaviour)->setFocusByController(true);
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
		changeP2->addComponent<GpadKeySwitcher>(1, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16, true);
		changeP2->addComponent<GpadKeySwitcherViewer>();
	}
	else {
		changeP2->addComponent<KeyboardKeySwitcher>(1, game_->getWindowWidth() / 4, game_->getWindowHeight() / 16);
		changeP2->addComponent<KeyboardKeySwitcherViewer>();
	}
}

void ConfigState::backButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getFSM()->popState();
}

void ConfigState::helperButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->getOptions().showKeyToPress = !SDLGame::instance()->getOptions().showKeyToPress;
}

void ConfigState::resButtonCallback(AnimalCooking* ac)
{
	SDLGame::instance()->getAudioMngr()->playChannel(Resources::AudioId::Tecla1 + SDLGame::instance()->getRandGen()->nextInt(0, 6), 0);
	SDLGame::instance()->toggleFullScreen();
}