#include "PlayersAdder.h"
#include "PlayerMotion.h"
#include "InteractionRect.h"
#include "Selector.h"
#include "Attack.h"
#include "Animator.h"
#include "PlayerController.h"
#include "PlayerViewer.h"
#include "LevelInitializer.h"

PlayersAdder::PlayersAdder(std::array<Entity*, 2>& players, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, const double casillaX, const double casillaY, EntityManager* em) :
	players(players), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral), casillaX(casillaX), casillaY(casillaY)
{
	for (int i = 0; i < players.size(); ++i) {
		players_initializeTransform(i, casillaX,casillaY);
		players_addComponents(players[i], i);
	}

	players[0]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::PigAttack),em,players[0]);
	players[1]->addComponent<PlayerViewer>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenIdle), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenWalk), SDLGame::instance()->getTextureMngr()->getTexture(Resources::ChickenAttack),em,players[1]);

	//Componentes extras
	for (int i = 0; i < players.size(); ++i) {
		jute::jValue components = jsonLevel["Players"][i]["components"];
		for (int c = 0; c < components.size(); ++c) { //Si tiene algun componente extra en ese nivel, se a�ade
			initializeComponent(components[c].as_string(), players[i]);
		}
	}
}

void PlayersAdder::players_addComponents(Entity* entity, int id)
{
	entity->addComponent<Animator>();
	entity->addComponent<PlayerMotion>();
	entity->addComponent<Selector>();
	InteractionRect* ir = entity->addComponent<InteractionRect>();
	entity->addComponent<Attack>();
	entity->addComponent<Transport>(ir);
	entity->addComponent<PlayerController>(id);
}

void PlayersAdder::players_initializeTransform(size_t player, const double casillaX, const double casillaY) // VER ENTITIES
{
	Transform* t = players[player]->addComponent<Transform>();

	t->setWH(jsonGeneral["Players"]["entities"][player]["size"]["width"].as_double() * casillaX,
		jsonGeneral["Players"]["entities"][player]["size"]["height"].as_double() * casillaY);

	t->setPos(Vector2D(jsonLevel["Players"][player]["pos"]["x"].as_double() * casillaX,
		jsonLevel["Players"][player]["pos"]["y"].as_double() * casillaY));

	t->setHitboxOffset(int(t->getW() * 0.1), int(t->getH() / 2));
	t->setHitboxSize(int(t->getW() * 0.8), int(t->getH() / 2));
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