#include "SDLGame.h"
#include "SDLFontsManager.h"
#include "SDLAudioManager.h"
#include "SDLTexturesManager.h"

#include <time.h>
#include <iostream>

#include "SRandBasedGenerator.h"
#include "FSM.h"
#include "SDL_macros.h"

unique_ptr<SDLGame> SDLGame::instance_;
const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";

SDLGame::SDLGame(string windowTitle, int width, int height) :currentLevel(0), unlockedLevels(0), maxLevels(0), score(0),maxScore(0),
		windowTitle_(windowTitle), width_(width), height_(height), timersViewer_(nullptr), options_(), imFullscreen() {
	initSDL();
	initResources();
}

SDLGame::~SDLGame() {
	closeResources();
	closeSDL();
}

void SDLGame::initSDL() {

	int sdlInit_ret = SDL_Init(SDL_INIT_EVERYTHING);
	assert(sdlInit_ret == 0);

	SDL_DisplayMode DM;
	SDL_GetCurrentDisplayMode(0, &DM);
	width_ = DM.w;
	height_ = DM.h;
	//height_ = 720;
	//width_ = 1080;

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_ - 40, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	SDL_RenderSetLogicalSize(renderer_, width_, height_);

	SDL_SetWindowResizable(window_, SDL_TRUE);

	// Clear screen (background color).
	int sdlSetDrawColor_ret = SDL_SetRenderDrawColor(renderer_, 0, 100, 100,
			255);  // Dark grey.
	assert(sdlSetDrawColor_ret != -1);
	int sdlRenderClear_ret = SDL_RenderClear(renderer_);
	assert(sdlRenderClear_ret != -1);
	SDL_RenderPresent(renderer_);

	//toggleFullScreen();

	// hide cursor by default
	//SDL_ShowCursor(0);
}

void SDLGame::closeSDL() {

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

void SDLGame::initResources() {

	fsm_ = new FSM();

	random_ = new SRandBasedGenerator();
	random_->init();

	textures_ = new SDLTexturesManager();
	textures_->init();

	fonts_ = new SDLFontsManager();
	fonts_->init();

	audio_ = new SDLAudioManager();
	audio_->init();

	for (auto &image : Resources::images_) {
		if(image.level == Resources::Level::Basic) textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	for (auto& spritesheet : Resources::spritesheets_) {
		if (spritesheet.level == Resources::Level::Basic) textures_->loadFromSprSheet(spritesheet.id, renderer_, spritesheet.fileName, spritesheet.numRows, spritesheet.numCols);
	}

	for (auto &font : Resources::fonts_) {
		if (font.level == Resources::Level::Basic) fonts_->loadFont(font.id, font.fileName, font.size);
	}

	for (auto &txtmsg : Resources::messages_) {
		if (txtmsg.level == Resources::Level::Basic) textures_->loadFromText(txtmsg.id, renderer_, txtmsg.msg,
				fonts_->getFont(txtmsg.fontId), txtmsg.color);
	}

	for (auto &sound : Resources::sounds_) {
		if (sound.level == Resources::Level::Basic) audio_->loadSound(sound.id, sound.fileName);
	}

	for (auto &music : Resources::musics_) {
		if (music.level == Resources::Level::Basic) audio_->loadMusic(music.id, music.fileName);
	}

	json_general = jute::parser::parse_file(rutaGeneral);
}

void SDLGame::closeResources() {
	delete fonts_;
	delete textures_;
	delete random_;
	delete audio_;
	delete fsm_;
}

void SDLGame::renderFeedBack(const Vector2D& position, const string& msg, const string& key)
{
	Texture name = Texture(SDLGame::instance()->getRenderer(), msg + " ",
		SDLGame::instance()->getFontMngr()->getFont(Resources::FontId::QuarkCheese50), { COLOR(0x000000ff) });

	Resources::FontId fuente = Resources::FontId::QuarkCheese50;
	//if (key.length() == 1) fuente = Resources::FontId::ARIAL50;

	Texture keyText = Texture(SDLGame::instance()->getRenderer(), key,
		SDLGame::instance()->getFontMngr()->getFont(fuente), { COLOR(0x000000ff) });

	//Ancho | alto del fondo
	int repeticiones;
	double height = 1;
	if (key.length() > 3) {
		const string& s = (msg.length() < key.length()) ? msg : key;
		repeticiones = s.length() / 3;
		height = 2;
	}
	else repeticiones = (msg.length() + key.length()) / 4;

	Vector2D pos = Vector2D(position.getX() + 50, position.getY() + height * 25);

	//FONDO
	Texture* borde = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::BordeTeclaFeedBack);
	Texture* relleno = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::RellenoTeclaFeedBack);
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height));
	pos.setX(pos.getX() + borde->getWidth());
	double startingPosRelleno = pos.getX();
	double lengthRelleno = 0;
	for (int i = 0; i < repeticiones; ++i) {
		relleno->render(RECT(pos.getX(), pos.getY(), relleno->getWidth(), relleno->getHeight() * height));
		pos.setX(pos.getX() + relleno->getWidth());
		lengthRelleno = pos.getX() - startingPosRelleno;
	}
	borde->render(RECT(pos.getX(), pos.getY(), borde->getWidth(), borde->getHeight() * height), 0.0,
		RECT(0, 0, borde->getWidth(), borde->getHeight()), SDL_FLIP_HORIZONTAL);

	SDL_Rect nameRect, keyRect;
	if (height == 1) { //En una fila
		nameRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + keyText.getWidth()) / 2,
			pos.getY() + borde->getHeight() / 2 - name.getHeight() / 2,
			name.getWidth() * name.getHeight() / double(name.getHeight()), name.getHeight());
		keyRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() + keyText.getWidth()) / 2 + name.getWidth(),
			pos.getY() + borde->getHeight() / 2 - name.getHeight() / 2,
			keyText.getWidth() * keyText.getHeight() / double(name.getHeight()), name.getHeight());
	}
	else { //En dos filas
		double textHeight = 0.8 * name.getHeight() + 0.8 * keyText.getHeight();
		nameRect = RECT(startingPosRelleno + lengthRelleno / 2 - (name.getWidth() / 2),
			pos.getY() + borde->getHeight() * height / 2 - textHeight / 2,
			name.getWidth() * 0.8 * name.getHeight() / double(0.8 * name.getHeight()), 0.8 * name.getHeight());
		keyRect = RECT(startingPosRelleno + lengthRelleno / 2 - (keyText.getWidth() / 2),
			pos.getY() + borde->getHeight() * height / 2 - textHeight / 2 + 0.9 * name.getHeight(),
			keyText.getWidth() * 0.8 * keyText.getHeight() / double(0.8 * keyText.getHeight()), 0.8 * keyText.getHeight());
	}
	name.render(nameRect);
	keyText.render(keyRect);
}
