#include "ScreenLoader.h"
#include "SDLGame.h"
#include "SDLAudioManager.h"
#include "ButtonBehaviour.h"
#include "ButtonRenderer.h"
#include "LoadingBarViewer.h"
#include "IngAdder.h"

#define MAKE(t) makeIngredient<t>(type, n)


const string rutaNivel = "../AnimalCooking/resources/cfg/nivel";
const string rutaGeneral = "../AnimalCooking/resources/cfg/general.cfg";

ScreenLoader::ScreenLoader(Resources::Level nivel) : emPlaystate(nullptr), level(nivel), jsonLevel(), jsonGeneral(), ingPoolEntity_(nullptr)
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
		buttonGo_->addComponent<ButtonBehaviour>(goToPlayState)->setActive(false);
		buttonGo_->addComponent<ButtonRenderer>(game_->getTextureMngr()->getTexture(Resources::Button), nullptr);

		resetResources();
		initialize();
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
	
	GETCMP2(buttonGo_, ButtonBehaviour)->setActive(true);
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

	updateLength(0.2);
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
	updateLength(0.2);
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
	updateLength(0.2);
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
	updateLength(0.2);
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
	updateLength(0.2);
}

void ScreenLoader::updateLength(double extra)
{
	GETCMP2(barraCarga_, LoadingBarViewer)->plusLength(extra);
	draw();
}

void ScreenLoader::initialize()
{
	emPlaystate = new EntityManager(SDLGame::instance());
	string ruta_ = rutaNivel + std::to_string(level) + ".cfg";

	jute::jValue jsonLevel = jute::parser::parse_file(ruta_); // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue jsonGeneral = jute::parser::parse_file(rutaGeneral); // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	initialize_players();
	initialize_ingredientsPool();
}

void ScreenLoader::initialize_players()
{
	for (int i = 0; i < players.size(); ++i) {
		players[i] = emPlaystate->addEntity();
		emPlaystate->addToGroup(players[i], static_cast<ecs::GroupID>(jsonGeneral["Players"]["Layer"].as_int() - 1));
		players_initializeTransform(i);
		players_addComponents(players[i]);
	}

	players[0]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
	players[1]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pollo));

	players_initializeExtraComponents();
}

void ScreenLoader::players_addComponents(Entity* entity)
{
	entity->addComponent<PlayerMotion>();
	entity->addComponent<Selector>();
	entity->addComponent<InteractionRect>();
	entity->addComponent<Attack>();
	entity->addComponent<Transport>();
	entity->addComponent<PlayerController>();
}

void ScreenLoader::players_initializeTransform(size_t player) // VER ENTITIES
{
	Transform* t = players[player]->addComponent<Transform>();
	t->setWH(jsonGeneral["Players"]["entities"][player]["size"]["width"].as_int(), jsonGeneral["Players"]["entities"][player]["size"]["height"].as_int());
	t->setPos(Vector2D(jsonLevel["Players"][player]["pos"]["x"].as_int(), jsonLevel["Players"][player]["pos"]["y"].as_int()));
}

void ScreenLoader::players_initializeExtraComponents()
{
	for (int i = 0; i < players.size(); ++i) {
		jute::jValue components = jsonLevel["Players"][i]["components"];
		if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
			for (int c = 0; c < components.size(); ++c) {
				initializeComponent(components[c].as_string(), players[i]);
			}
		}
	}
}

void ScreenLoader::initialize_ingredientsPool()
{
	//Ingredientes----------------------------------------
	ingPoolEntity_ = stage->addEntity();

	stage->addToGroup(ingPoolEntity_, ecs::Layer3);

	ingPoolEntity_->addComponent<IngredientsPool>();
	ingPoolEntity_->addComponent<IngredientViewer>();
	ingPoolEntity_->addComponent<IngredientMotion>();

	IngAdder(ingPoolEntity_, jsonLevel, jsonGeneral);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void ScreenLoader::initializeComponent(const string& component, Entity* entity) //La cadena no puede superar 10 caracteres
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}

void ScreenLoader::goToPlayState() {
	SDLGame::instance()->getFSM()->changeState(new PlayState());
}