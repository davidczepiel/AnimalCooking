#include "SinkAdder.h"
#include "Manager.h"
#include "Sink.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)

SinkAdder::SinkAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casillaLength) : em(em)
{
	jute::jValue sinks_ = jsonLevel["Sink"]["entities"];
	jute::jValue components = jsonLevel["Sink"]["components"];

	for (int i = 0; i < sinks_.size(); ++i) {
		Sink* sink = new Sink(Vector2D(sinks_[i]["pos"]["x"].as_double() * casillaLength, sinks_[i]["pos"]["y"].as_double() * casillaLength),
			GETCMP2(player[0], Transport), GETCMP2(player[1], Transport), em);

		sink->setSize(Vector2D(jsonGeneral["Sink"]["size"]["width"].as_double() * casillaLength,
			jsonGeneral["Sink"]["size"]["height"].as_double() * casillaLength));
		sink->addComponent<SelectorPopUpEntity>(GETCMP2(player[0],InteractionRect), GETCMP2(player[1], InteractionRect), GETCMP2(player[0], Selector), GETCMP2(player[1],Selector),sink);

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