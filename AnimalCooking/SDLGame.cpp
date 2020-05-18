#include "SDLGame.h"
#include "SDLFontsManager.h"
#include "SDLAudioManager.h"
#include "SDLTexturesManager.h"

#include <time.h>
#include <iostream>

#include "SRandBasedGenerator.h"
#include "FSM.h"

unique_ptr<SDLGame> SDLGame::instance_;
const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";


SDLGame::SDLGame(string windowTitle, int width, int height) :currentLevel(0), unlockedLevels(0), maxLevels(0), score(0),maxScore(0),
		windowTitle_(windowTitle), width_(width), height_(height), timersViewer_(nullptr), options_() {
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
	height_ = 720;
	width_ = 1080;

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_ - 60, SDL_WINDOW_SHOWN);
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
