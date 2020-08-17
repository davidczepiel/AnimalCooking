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


ConfigState::ConfigState(AnimalCooking* ac) : State(ac),
game_(SDLGame::instance()), musicLastValue_(0.5), soundLastValue(0.5)
{
	initSliders();
	loadFromFile();
	initButtons();
	initKeyModifiers();
}

ConfigState::~ConfigState()
{
	saveToFile();
}

void ConfigState::saveToFile()
{
	config::Options& o = game_->getOptions();
	ofstream f;
	f.open("../AnimalCooking/resources/cfg/options.txt");
	if (f.is_open()) {
		saveVolumeSetting(f);
		saveBooleansSetting(f);
		savePlayer(f, 0, o);
		savePlayer(f, 1, o);
	}
	f.close();
}

void ConfigState::loadFromFile()
{
	config::Options& o = game_->getOptions();
	ifstream f;
	f.open("../AnimalCooking/resources/cfg/options.txt");
	if (f.is_open()) {
		loadVolumeSetting(f);
		loadBooleansSetting(f);
		loadPlayer(f, 0, o);
		loadPlayer(f, 1, o);
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

void ConfigState::saveBooleansSetting(ofstream& f)
{
	f << game_->getIfFullscreen() << " " << game_->getOptions().showKeyToPress << endl;
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
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].PICKUP = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].ATTACK = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].OPEN = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].PREVIOUS = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].NEXT = (SDL_GameControllerButton)aux;
	f >> aux; if (!f.fail()) o.players_gPadButtons[player].FINISHER = (SDL_GameControllerButton)aux;
}

void ConfigState::loadVolumeSetting(ifstream& f)
{
	float value;
	f >> value; sliderMusic_->movePercentage(value);
	f >> value; sliderSound_->movePercentage(value);
}

void ConfigState::loadBooleansSetting(ifstream& f)
{
	bool value;
	f >> value; if (value && !game_->getIfFullscreen()) game_->toggleFullScreen();
	f >> value; game_->getOptions().showKeyToPress = value;
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
	drawNoInteractuables();
	State::draw();
}

void ConfigState::drawNoInteractuables()
{
	//Background
	SDL_Rect dest = RECT(0, 0, game_->getWindowWidth(), game_->getWindowHeight());
	game_->getTextureMngr()->getTexture(Resources::Config_Background)->render(dest);

	//Options Title
	dest = RECT(0, 0, game_->getWindowWidth(), 173);
	game_->getTextureMngr()->getTexture(Resources::Config_OptionsTitle)->render(dest);

	//Music Icon
	dest = RECT(100, 410, 80, 88);
	game_->getTextureMngr()->getTexture(Resources::Config_MusicIcon)->render(dest);

	//Sounds Icon
	dest = RECT(100, 530, 88, 78);
	game_->getTextureMngr()->getTexture(Resources::Config_SoundIcon)->render(dest);

	//Music Text
	dest = RECT(200, 380, 164, 33);
	game_->getTextureMngr()->getTexture(Resources::Config_MusicVolumeTitle)->render(dest);

	//Sounds Text
	dest = RECT(200, 500, 181, 32);
	game_->getTextureMngr()->getTexture(Resources::Config_SoundVolumeTitle)->render(dest);

	//Panel Izquierdo
	dest = RECT(780, 235, 550, 794);
	game_->getTextureMngr()->getTexture(Resources::Config_Panel)->render(dest);

	//Panel Derecho
	dest = RECT(1350, 235, 550, 794);
	game_->getTextureMngr()->getTexture(Resources::Config_Panel)->render(dest);

	//Player 1
	dest = RECT(830, 210, 320, 140);
	game_->getTextureMngr()->getTexture(Resources::Config_Player1)->render(dest);

	//PLayer 2
	dest = RECT(1400, 210, 332, 140);
	game_->getTextureMngr()->getTexture(Resources::Config_Player2)->render(dest);
}


void ConfigState::initButtons()
{
	//Back button
	salir = stage->addEntity();
	stage->addToGroup(salir, ecs::GroupID::ui);
	salir->addComponent<Transform>(
		Vector2D(90, 120),
		Vector2D(), 275, 235, 0);
	ButtonBehaviour* bb = salir->addComponent<ButtonBehaviour>(backButtonCallback, app);
	ButtonRenderer* br = salir->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Config_BackButton), nullptr);
	bb->setButtonRenderer(br);

	//Toggle Window / Fullscreen
	res = stage->addEntity();
	stage->addToGroup(res, ecs::GroupID::ui);
	res->addComponent<Transform>(
		Vector2D(175, 650),
		Vector2D(), 499, 90, 0);
	bb = res->addComponent<ButtonBehaviour>(resButtonCallback, app);
	res->addComponent<ButtonChangeOnClick>(game_->getIfFullscreen());
	br = res->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Config_FullscreenButton), nullptr);
	bb->setButtonRenderer(br);

	//Helper button
	helper = stage->addEntity();
	stage->addToGroup(helper, ecs::GroupID::ui);
	helper->addComponent<Transform>(
		Vector2D(203, 750),
		Vector2D(), 499, 90, 0);
	bb = helper->addComponent<ButtonBehaviour>(helperButtonCallback, app);
	helper->addComponent<ButtonChangeOnClick>(game_->getOptions().showKeyToPress);
	br = helper->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Config_ReminderButton), nullptr);
	bb->setButtonRenderer(br);

}

void ConfigState::initSliders()
{
	//Slider for Music
	sliderTop = stage->addEntity();
	stage->addToGroup(sliderTop, ecs::GroupID::ui);
	Transform* t = sliderTop->addComponent<Transform>(
		Vector2D(210, 440),
		Vector2D(), 460, 30, 0);
	sliderMusic_ = sliderTop->addComponent<SliderBehaviour>();
	sliderTop->addComponent<SliderRenderer>();
	sliderMusic_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.music_ / 128.0);

	//Slider for Sound Effects
	sliderBot = stage->addEntity();
	stage->addToGroup(sliderBot, ecs::GroupID::ui);
	t = sliderBot->addComponent<Transform>(
		Vector2D(210, 560),
		Vector2D(), 460, 30, 0);
	sliderSound_ = sliderBot->addComponent<SliderBehaviour>();
	sliderBot->addComponent<SliderRenderer>();
	sliderSound_->getMovePointRect()->x = t->getPos().getX() + t->getW() * (game_->getOptions().volume.sounds_ / 128.0);
}

void ConfigState::initKeyModifiers()
{
	GPadController* gpCont = GPadController::instance();

	//Player1 Left
	changeP1 = stage->addEntity();
	stage->addToGroup(changeP1, ecs::GroupID::ui);
	changeP1->addComponent<Transform>(
		Vector2D(808, 375),
		Vector2D(), 535, 630, 0);

	if (gpCont->playerControllerConnected(0)) {
		changeP1->addComponent<GpadKeySwitcher>(0, 535, 105, false);
		changeP1->addComponent<GpadKeySwitcherViewer>(game_->getTextureMngr()->getTexture(Resources::Config_CerdoClick));

		Entity* e = stage->addEntity();
		ButtonPadNavigation* bp = e->addComponent<ButtonPadNavigation>();
		bp->onlyListenTo(0);
		bp->AddButton(changeP1, nullptr, nullptr, salir, nullptr, true);
		bp->AddButton(salir, nullptr, sliderTop, nullptr, changeP1);
		bp->AddButton(res, sliderBot, helper, nullptr, changeP1);
		bp->AddButton(helper, res, nullptr, nullptr, changeP1);
		bp->AddButton(sliderTop, salir, sliderBot, nullptr, changeP1, true);
		bp->AddButton(sliderBot, sliderTop, res, nullptr, changeP1, true);
	}
	else {
		changeP1->addComponent<KeyboardKeySwitcher>(0, 535, 105);
		changeP1->addComponent<KeyboardKeySwitcherViewer>(game_->getTextureMngr()->getTexture(Resources::Config_CerdoClick));
	}

	//Player2 Right
	changeP2 = stage->addEntity();
	stage->addToGroup(changeP2, ecs::GroupID::ui);
	changeP2->addComponent<Transform>(
		Vector2D(1378, 375),
		Vector2D(), 535, 630, 0);
	if (gpCont->playerControllerConnected(1)) {
		changeP2->addComponent<GpadKeySwitcher>(1, 535, 105, true);
		changeP2->addComponent<GpadKeySwitcherViewer>(game_->getTextureMngr()->getTexture(Resources::Config_ChickenClick));
	}
	else {
		changeP2->addComponent<KeyboardKeySwitcher>(1, 535, 105);
		changeP2->addComponent<KeyboardKeySwitcherViewer>(game_->getTextureMngr()->getTexture(Resources::Config_ChickenClick));
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