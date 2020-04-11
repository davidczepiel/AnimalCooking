#include "BinAdder.h"
#include "Manager.h"
#include "BinEntity.h"
#include "SelectorPopUpEntity.h"

#define CASTID(t) static_cast<ecs::GroupID>(t - 1)
#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)

BinAdder::BinAdder(EntityManager* em, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player, const double casillaLength) : em(em)
{
	jute::jValue bins_ = jsonLevel["Bin"]["entities"];
	jute::jValue components = jsonLevel["Bin"]["components"];

	for (int i = 0; i < bins_.size(); ++i) {
		BinEntity* bin = new BinEntity(em, GIVETRANSPORT);

		bin->setSize(Vector2D(jsonGeneral["Bin"]["size"]["width"].as_double() * casillaLength,
			jsonGeneral["Sink"]["size"]["height"].as_double() * casillaLength));

		bin->setPos(Vector2D(bins_[i]["pos"]["x"].as_double() * casillaLength,
			bins_[i]["pos"]["y"].as_double() * casillaLength));

		em->addEntity(bin);
		em->addToGroup(bin, CASTID(jsonGeneral["Bin"]["Layer"].as_int()));

		bin->addComponent<BinViewer>(bin);
		bin->addComponent<SelectorPopUpEntity>(GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
			GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), bin);

		for (int i = 0; i < components.size(); ++i) { // Iniciliza en bin componentes extra si los hay
			initializeComponent(components[i].as_string(), bin);
		}
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

//La cadena (component) no puede superar 10 caracteres
void BinAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}