#include "UtensilsAdder.h"
#include "SelectorPopUp.h"
#include "UtensilsViewer.h"
#include "UtensilsPool.h"
#include "UtensilsMotion.h"

#define GIVETRANSPORT GETCMP2(player[0], Transport), GETCMP2(player[1], Transport)
#define ADD(t) makeUtensil<t>(player)

UtensilsAdder::UtensilsAdder(Entity* utensilsPool, jute::jValue jsonLevel, jute::jValue jsonGeneral, std::array<Entity*, 2>& player) :
	utensilsPool(utensilsPool), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	//Componentes basicos
	UtensilsPool* pool_ = utensilsPool->addComponent<UtensilsPool>();
	utensilsPool->addComponent<SelectorPopUp>(&reinterpret_cast<vector<Interactive*>&>(pool_->getPool()), GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), GETCMP2(player[0], Transport), GETCMP2(player[1], Transport));
	utensilsPool->addComponent<UtensilsViewer>();
	utensilsPool->addComponent<UtensilsMotion>();

	//Se meten los distintos utensilios a la pool
	jute::jValue utensTypes = jsonLevel["UtensilPool"]["entities"];
	for (int i = 0; i < utensTypes.size(); ++i) {
		switchUten(jsonLevel["UtensilPool"]["entities"][i].as_string(), pool_, player);
	}

	//Se meten los componentes especificos de ese nivel
	jute::jValue components = jsonLevel["UtensilPool"]["components"];
	if (components.size() > 0) { //Si tiene algun componente extra en ese nivel
		for (int c = 0; c < components.size(); ++c) {
			initializeComponent(components[c].as_string(), utensilsPool);
		}
	}
}

template <typename T>
void UtensilsAdder::makeUtensil(std::array<Entity*, 2>& player)
{
	Utensil* u = new T(GIVETRANSPORT);
	u->setSize(Vector2D(jsonGeneral["Utensils"]["size"]["width"].as_int(), jsonGeneral["Utensils"]["size"]["height"].as_int()));
	GETCMP2(utensilsPool, UtensilsPool)->addUtensil(u);
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

void UtensilsAdder::switchUten(const string& ing, UtensilsPool* pool_, std::array<Entity*, 2>& player)
{
	switch (str2int(ing.c_str()))
	{
	case str2int("Knife"):
		ADD(Knife);
		break;
	case str2int("Mace"):
		ADD(Knife);
		break;
	default:
		break;
	}
}

//La cadena (component) no puede superar 10 caracteres
void UtensilsAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}
