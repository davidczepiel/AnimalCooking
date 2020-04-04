#include "PlayersAdder.h"
#include "PlayerMotion.h"
#include "InteractionRect.h"
#include "Selector.h"
#include "Attack.h"
#include "PlayerController.h"
#include "PlayerViewer.h"
#include "LevelInitializer.h"

PlayersAdder::PlayersAdder(std::array<Entity*, 2>& players, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, LevelInitializer* li) :
	players(players), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	for (int i = 0; i < players.size(); ++i) {
		players_initializeTransform(i);
		players_addComponents(players[i]);
	}

	players[0]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Cerdo));
	players[1]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Pollo));

	players_initializeExtraComponents(li);
}

void PlayersAdder::players_addComponents(Entity* entity)
{
	entity->addComponent<PlayerMotion>();
	entity->addComponent<Selector>();
	entity->addComponent<InteractionRect>();
	entity->addComponent<Attack>();
	entity->addComponent<Transport>();
	entity->addComponent<PlayerController>();
}

void PlayersAdder::players_initializeTransform(size_t player) // VER ENTITIES
{
	Transform* t = players[player]->addComponent<Transform>();
	t->setWH(jsonGeneral["Players"]["entities"][player]["size"]["width"].as_int(), jsonGeneral["Players"]["entities"][player]["size"]["height"].as_int());
	t->setPos(Vector2D(jsonLevel["Players"][player]["pos"]["x"].as_int(), jsonLevel["Players"][player]["pos"]["y"].as_int()));
}

void PlayersAdder::players_initializeExtraComponents(LevelInitializer* li)
{
	for (int i = 0; i < players.size(); ++i) {
		jute::jValue components = jsonLevel["Players"][i]["components"];
		if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
			for (int c = 0; c < components.size(); ++c) {
				li->initializeComponent(components[c].as_string(), players[i]);
			}
		}
	}
}