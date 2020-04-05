#include "UtensilsAdder.h"
#include "SelectorPopUp.h"
#include "UtensilsViewer.h"
#include "UtensilsPool.h"
#include "UtensilsMotion.h"

UtensilsAdder::UtensilsAdder(Entity* utensilsPool, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, std::array<Entity*, 2>& player) :
	utensilsPool(utensilsPool), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)
{
	//Componentes basicos
	UtensilsPool* pool_ = utensilsPool->addComponent<UtensilsPool>();
	utensilsPool->addComponent<SelectorPopUp>(&reinterpret_cast<vector<Interactive*>&>(pool_->getPool()), GETCMP2(player[0], InteractionRect), GETCMP2(player[1], InteractionRect),
		GETCMP2(player[0], Selector), GETCMP2(player[1], Selector), GETCMP2(player[0], Transport), GETCMP2(player[1], Transport));
	utensilsPool->addComponent<UtensilsViewer>();
	utensilsPool->addComponent<UtensilsMotion>();

	//Se meten los componentes especificos de ese nivel
	jute::jValue components = jsonLevel["UtensilPool"]["components"];
	for (int c = 0; c < components.size(); ++c) { //Si tiene algun componente extra en ese nivel, se añade
		initializeComponent(components[c].as_string(), utensilsPool);
	}
}

constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
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