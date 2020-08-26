#include "SinkAdder.h"
#include "Manager.h"
#include "Sink.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

SinkAdder::SinkAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casillaX, const double casillaY) : em(em)
{
	jute::jValue sinks_ = jsonLevel["Sink"]["entities"];
	jute::jValue components = jsonLevel["Sink"]["components"];

	for (int i = 0; i < sinks_.size(); ++i) {

		Texture* t1 = nullptr;
		Texture* t2 = nullptr;

		//se escoje la textura del fregadero
		if(sinks_[i]["texture"].as_string() == "flip") //mkrando hacia la derecha
		{
			t1 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoFlip);
			t2 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoFlipON);
		}
		else if (sinks_[i]["texture"].as_string() == "down") //mirando hacia abajo
		{
			t1 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoAbajo);
			t2 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoAbajoON);
		}
		else if (sinks_[i]["texture"].as_string() == "FregaderoBordeIzq")
		{
			t1 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoBordeIzq);
			t2 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoBordeIzqON);
		}
		else if (sinks_[i]["texture"].as_string() == "esqSupDer")
		{
			t1 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoEsqDchaArr);
			t2 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoEsqDchaArrON);
		}
		else //mirando hacia la izquierda
		{
			t1 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::Fregadero);
			t2 = SDLGame::instance()->getTextureMngr()->getTexture(Resources::TextureId::FregaderoON);
		}

		Sink* sink = new Sink(Vector2D(sinks_[i]["pos"]["x"].as_double() * casillaX, sinks_[i]["pos"]["y"].as_double() * casillaY),
			GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), em,t1,t2);

		sink->setSize(Vector2D(jsonGeneral["Sink"]["size"]["width"].as_double() * casillaX,
			jsonGeneral["Sink"]["size"]["height"].as_double() * casillaY));
		sink->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect), GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), sink);

		sink->setHitboxSize(Vector2D(sink->getSize().getX(), sink->getSize().getY()));

		em->addEntity(sink);
		em->addToGroup(sink, CASTID(jsonGeneral["Sink"]["Layer"].as_int()));

		for (int i = 0; i < components.size(); ++i) { // Iniciliza en sink componentes extra si los hay
			initializeComponent(components[i].as_string(), sink);
		}
		interactives_.push_back(sink);
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void SinkAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}