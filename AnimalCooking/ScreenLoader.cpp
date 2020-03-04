#include "ScreenLoader.h"
#include "SDLGame.h"
#include "SDLAudioManager.h"

ScreenLoader::ScreenLoader(Resources::Level nivel)
{
		Entity* menu_ = stage->addEntity();
		Entity* mensajes_ = stage->addEntity();

		barraCarga_ = stage->addEntity();

		buttonGo_ = stage->addEntity();

		resetResources(nivel);
}
		
//Carga en memoria los recursos asociados a un nivel en especifico, y si no estan cargados los recursos comunes a todos los niveles, los carga
//Si esta cargado en memoria algun recurso que no pertenezca a ese nivel, se descarga de memoria
//Va actualizando la barra de progreso y renderizandolo
void ScreenLoader::resetResources(Resources::Level level)
{
	SDL_Renderer* renderer_ = SDLGame::instance()->getRenderer();

	loadTextures(level, renderer_);
	loadFonts(level);
	loadMessagges(level, renderer_);
	loadSounds(level);
	loadMusics(level);
	//GETCMP2(buttonGo_, Active)->setActive();
}

void ScreenLoader::loadTextures(Resources::Level level, SDL_Renderer* renderer_)
{
	TexturesManager* textures_ = SDLGame::instance()->getTextureMngr();

	for (auto& image : Resources::images_) {
		//Si la imagen no pertenece al nivel y esta cargada en memoria, se elimina
		if (image.id != Resources::Level::Basic && image.id != Resources::Level::AllLevels && image.id != level &&
			textures_->getTexture(image.id) != nullptr) {
			textures_->destroyTexture(image.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (textures_->getTexture(image.id) == nullptr) textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	updateLength(0.2);
}

void ScreenLoader::loadFonts(Resources::Level level)
{
	FontsManager* fonts_ = SDLGame::instance()->getFontMngr();

	for (auto& font : Resources::fonts_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (font.id != Resources::Level::Basic && font.id != Resources::Level::AllLevels && font.id != level &&
			fonts_->getFont(font.id) != nullptr) {
			fonts_->destroyFont(font.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (fonts_->getFont(font.id) == nullptr) fonts_->loadFont(font.id, font.fileName, font.size);
	}
	updateLength(0.2);
}

void ScreenLoader::loadSounds(Resources::Level level)
{
	SDLAudioManager* audio_ = static_cast<SDLAudioManager*>(SDLGame::instance()->getAudioMngr());

	for (auto& sound : Resources::sounds_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (sound.id != Resources::Level::Basic && sound.id != Resources::Level::AllLevels && sound.id != level &&
			audio_->getSound(sound.id) != nullptr) {
			audio_->destroySound(sound.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getSound(sound.id) == nullptr) audio_->loadSound(sound.id, sound.fileName);
	}
	updateLength(0.2);
}

void ScreenLoader::loadMusics(Resources::Level level)
{
	SDLAudioManager* audio_ = static_cast<SDLAudioManager*>(SDLGame::instance()->getAudioMngr());

	for (auto& music : Resources::musics_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (music.id != Resources::Level::Basic && music.id != Resources::Level::AllLevels && music.id != level &&
			audio_->getMusic(music.id) != nullptr) {
			audio_->destroyMusic(music.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getMusic(music.id) == nullptr) audio_->loadMusic(music.id, music.fileName);
	}
	updateLength(0.2);
}

void ScreenLoader::loadMessagges(Resources::Level level, SDL_Renderer* renderer_)
{
	TexturesManager* textures_ = SDLGame::instance()->getTextureMngr();
	FontsManager* fonts_ = SDLGame::instance()->getFontMngr();

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
	updateLength(0.2);
}

void ScreenLoader::updateLength(double extra)
{
	//GETCMP2(barraCarga_, Length)->plusLength(extra);
	Draw();
}
