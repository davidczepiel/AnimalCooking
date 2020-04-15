#include "PlayersAdder.h"
#include "PlayerMotion.h"
#include "InteractionRect.h"
#include "Selector.h"
#include "Attack.h"
#include "Animator.h"
#include "PlayerController.h"
#include "PlayerViewer.h"
#include "LevelInitializer.h"

PlayersAdder::PlayersAdder(std::array<Entity*, 2>& players, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, const double casillaLength) :
	players(players), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	for (int i = 0; i < players.size(); ++i) {
		players_initializeTransform(i, casillaLength);
		players_addComponents(players[i], i);
	}

	players[0]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
	players[1]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pollo));

	//Componentes extras
	for (int i = 0; i < players.size(); ++i) {
		jute::jValue components = jsonLevel["Players"][i]["components"];
		for (int c = 0; c < components.size(); ++c) { //Si tiene algun componente extra en ese nivel, se añade
			initializeComponent(components[c].as_string(), players[i]);
		}
	}
}

void PlayersAdder::players_addComponents(Entity* entity, int id)
{
	entity->addComponent<Animator>();
	entity->addComponent<PlayerMotion>();
	entity->addComponent<Selector>();
	entity->addComponent<InteractionRect>();
	entity->addComponent<Attack>();
	entity->addComponent<Transport>();
	entity->addComponent<PlayerController>(id);
}

void PlayersAdder::players_initializeTransform(size_t player, const double casillaLength) // VER ENTITIES
{
	Transform* t = players[player]->addComponent<Transform>();

	t->setWH(jsonGeneral["Players"]["entities"][player]["size"]["width"].as_double() * casillaLength,
		jsonGeneral["Players"]["entities"][player]["size"]["height"].as_double() * casillaLength);

	t->setPos(Vector2D(jsonLevel["Players"][player]["pos"]["x"].as_double() * casillaLength,
		jsonLevel["Players"][player]["pos"]["y"].as_double() * casillaLength));
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void PlayersAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}