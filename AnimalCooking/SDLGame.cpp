#include "SDLGame.h"
#include "SDLFontsManager.h"
#include "SDLAudioManager.h"
#include "SDLTexturesManager.h"

#include <time.h>
#include <iostream>

#include "SRandBasedGenerator.h"


unique_ptr<SDLGame> SDLGame::instance_;


SDLGame::SDLGame(string windowTitle, int width, int height) :
		windowTitle_(windowTitle), width_(width), height_(height) {
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

	// Create window
	window_ = SDL_CreateWindow(windowTitle_.c_str(),
	SDL_WINDOWPOS_UNDEFINED,
	SDL_WINDOWPOS_UNDEFINED, width_, height_, SDL_WINDOW_SHOWN);
	assert(window_ != nullptr);

	// Create the renderer
	renderer_ = SDL_CreateRenderer(window_, -1,
			SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	assert(renderer_ != nullptr);

	// Clear screen (background color).
	int sdlSetDrawColor_ret = SDL_SetRenderDrawColor(renderer_, 0, 100, 100,
			255);  // Dark grey.
	assert(sdlSetDrawColor_ret != -1);
	int sdlRenderClear_ret = SDL_RenderClear(renderer_);
	assert(sdlRenderClear_ret != -1);
	SDL_RenderPresent(renderer_);

	// hide cursor by default
	SDL_ShowCursor(0);

}

void SDLGame::closeSDL() {

	SDL_DestroyRenderer(renderer_);
	renderer_ = nullptr;

	SDL_DestroyWindow(window_);
	window_ = nullptr;

	SDL_Quit();
}

void SDLGame::initResources() {

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

}

void SDLGame::closeResources() {
	delete fonts_;
	delete textures_;
	delete random_;
	delete audio_;
}

//Carga en memoria los recursos asociados a un nivel en especifico, y si no estan cargados los recursos comunes a todos los niveles los carga
//Si esta cargado en memoria algun recurso que no pertenezca a ese nivel, se descarga de memoria
void SDLGame::load(Resources::Level level)
{
	// TODO: mover la barra de progreso 

	for (auto& image : Resources::images_) {
		//Si la imagen no pertenece al nivel y esta cargada en memoria, se elimina
		if (image.id != Resources::Level::Basic && image.id != Resources::Level::AllLevels && image.id != level && 
			textures_->getTexture(image.id) != nullptr) {
			textures_->destroyTexture(image.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (textures_->getTexture(image.id) == nullptr) textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	for (auto& font : Resources::fonts_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (font.id != Resources::Level::Basic && font.id != Resources::Level::AllLevels && font.id != level &&
			fonts_->getFont(font.id) != nullptr) {
			fonts_->destroyFont(font.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (fonts_->getFont(font.id) == nullptr) fonts_->loadFont(font.id, font.fileName, font.size);
	}

	for (auto& txtmsg : Resources::messages_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (txtmsg.id != Resources::Level::Basic && txtmsg.id != Resources::Level::AllLevels && txtmsg.id != level &&
			textures_->getTexture(txtmsg.id) != nullptr) {
			textures_->destroyTexture(txtmsg.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (fonts_->getFont(txtmsg.id) == nullptr) 
			textures_->loadFromText(txtmsg.id, renderer_, txtmsg.msg, fonts_->getFont(txtmsg.fontId), txtmsg.color);
	}

	for (auto& sound : Resources::sounds_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (sound.id != Resources::Level::Basic && sound.id != Resources::Level::AllLevels && sound.id != level &&
			audio_->getSound(sound.id) != nullptr) {
			audio_->destroySound(sound.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getSound(sound.id) == nullptr) audio_->loadSound(sound.id, sound.fileName);
	}

	for (auto& music : Resources::musics_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (music.id != Resources::Level::Basic && music.id != Resources::Level::AllLevels && music.id != level &&
			audio_->getMusic(music.id) != nullptr) {
			audio_->destroyMusic(music.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getMusic(music.id) == nullptr) audio_->loadMusic(music.id, music.fileName);
	}
}