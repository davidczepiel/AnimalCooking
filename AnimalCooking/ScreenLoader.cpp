#include "ScreenLoader.h"
#include "SDLGame.h"
#include "SDLAudioManager.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "LoadingBarViewer.h"
#include "LevelInitializer.h"

constexpr double step_ = 1.0 / 18.0; //18 es el numero de pasos (5 de carga de recursos + 13 de carga de nivel)

ScreenLoader::ScreenLoader(Resources::Level nivel, AnimalCooking* ac) :State(ac), emPlaystate(nullptr), level(nivel)
{
	Entity* menu_ = stage->addEntity();
	Entity* mensajes_ = stage->addEntity();

	barraCarga_ = stage->addEntity();
	stage->addToGroup(barraCarga_, ecs::GroupID::Layer1);

	SDLGame* game_ = SDLGame::instance();
	int width = SDLGame::instance()->getWindowWidth() / 5;
	barraCarga_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 - width / 2, game_->getWindowHeight() / 1.2), //Pos
		Vector2D(), //Dir
		width, //Width
		50, //Height
		0); //Rot
	barraCarga_->addComponent<LoadingBarViewer>(game_->getTextureMngr()->getTexture(Resources::Button),
		game_->getTextureMngr()->getTexture(Resources::Button));

	buttonGo_ = stage->addEntity();
	stage->addToGroup(buttonGo_, ecs::GroupID::Layer1);

	buttonGo_->addComponent<Transform>(Vector2D(game_->getWindowWidth() / 2 + width / 1.5, game_->getWindowHeight() / 1.25), //Pos
		Vector2D(), //Dir
		50, //Width
		50, //Height
		0); //Rot

	buttonGo_->addComponent<ButtonBehaviour>(goToPlayState,app)->setActive(false);
	buttonGo_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);

	resetResources();
	initialize();

	GETCMP2(buttonGo_, ButtonBehaviour)->setActive(true);
}

//Carga en memoria los recursos asociados a un nivel en especifico, y si no estan cargados los recursos comunes a los niveles, los carga
//Si esta cargado en memoria algun recurso que no pertenezca a ese nivel, se descarga de memoria
//Va actualizando la barra de progreso y renderizandolo
void ScreenLoader::resetResources()
{
	SDL_Renderer* renderer_ = SDLGame::instance()->getRenderer();

	loadTextures(renderer_);
	loadFonts();
	loadMessagges(renderer_);
	loadSounds();
	loadMusics();
}

void ScreenLoader::loadTextures(SDL_Renderer* renderer_)
{
	TexturesManager* textures_ = SDLGame::instance()->getTextureMngr();

	for (auto& image : Resources::images_) {
		//Si la imagen no pertenece al nivel y esta cargada en memoria, se elimina
		if (image.level != Resources::Level::Basic && image.level != Resources::Level::AllLevels && image.level != level &&
			textures_->getTexture(image.id) != nullptr) {
			textures_->destroyTexture(image.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (textures_->getTexture(image.id) == nullptr) textures_->loadFromImg(image.id, renderer_, image.fileName);
	}

	updateLength();
}

void ScreenLoader::loadFonts()
{
	FontsManager* fonts_ = SDLGame::instance()->getFontMngr();

	for (auto& font : Resources::fonts_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (font.level != Resources::Level::Basic && font.level != Resources::Level::AllLevels && font.level != level &&
			fonts_->getFont(font.id) != nullptr) {
			fonts_->destroyFont(font.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (fonts_->getFont(font.id) == nullptr) fonts_->loadFont(font.id, font.fileName, font.size);
	}
	updateLength();
}

void ScreenLoader::loadSounds()
{
	SDLAudioManager* audio_ = static_cast<SDLAudioManager*>(SDLGame::instance()->getAudioMngr());

	for (auto& sound : Resources::sounds_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (sound.level != Resources::Level::Basic && sound.level != Resources::Level::AllLevels && sound.level != level &&
			audio_->getSound(sound.id) != nullptr) {
			audio_->destroySound(sound.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getSound(sound.id) == nullptr) audio_->loadSound(sound.id, sound.fileName);
	}
	updateLength();
}

void ScreenLoader::loadMusics()
{
	SDLAudioManager* audio_ = static_cast<SDLAudioManager*>(SDLGame::instance()->getAudioMngr());

	for (auto& music : Resources::musics_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (music.level != Resources::Level::Basic && music.level != Resources::Level::AllLevels && music.level != level &&
			audio_->getMusic(music.id) != nullptr) {
			audio_->destroyMusic(music.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (audio_->getMusic(music.id) == nullptr) audio_->loadMusic(music.id, music.fileName);
	}
	updateLength();
}

void ScreenLoader::loadMessagges(SDL_Renderer* renderer_)
{
	TexturesManager* textures_ = SDLGame::instance()->getTextureMngr();
	FontsManager* fonts_ = SDLGame::instance()->getFontMngr();

	for (auto& txtmsg : Resources::messages_) {
		//Si la fuente no pertenece al nivel y esta cargada en memoria, se elimina
		if (txtmsg.level != Resources::Level::Basic && txtmsg.level != Resources::Level::AllLevels && txtmsg.level != level &&
			textures_->getTexture(txtmsg.id) != nullptr) {
			textures_->destroyTexture(txtmsg.id);
		}
		//Si pertenece al nivel y no esta cargada, se carga
		else if (fonts_->getFont(txtmsg.id) == nullptr)
			textures_->loadFromText(txtmsg.id, renderer_, txtmsg.msg, fonts_->getFont(txtmsg.fontId), txtmsg.color);
	}
	updateLength();
}

void ScreenLoader::updateLength()
{
	GETCMP2(barraCarga_, LoadingBarViewer)->plusLength(step_);
	draw();
}

//Inicializa el nivel
void ScreenLoader::initialize()
{
	emPlaystate = new EntityManager(SDLGame::instance());

	LevelInitializer(emPlaystate, level, this);
}

void ScreenLoader::goToPlayState(AnimalCooking* ac) {
	SDLGame::instance()->getFSM()->changeState(new PlayState(static_cast<ScreenLoader*>(SDLGame::instance()->getFSM()->currentState())->getEntityManager(),ac));
}