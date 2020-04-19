#include "IngAdder.h"
#include "IngredientsPool.h"
#include "LevelInitializer.h"
#include "IngredientViewer.h"
#include "IngredientMotion.h"


IngAdder::IngAdder(Entity* ing, jute::jValue& jsonLevel, jute::jValue& jsonGeneral/*, const double casillaLength*/) :
	ingPoolEntity_(ing), jsonLevel(jsonLevel), jsonGeneral(jsonGeneral)/*, casillaLength(casillaLength)*/
{
	ingPoolEntity_->addComponent<IngredientsPool>();
	ingPoolEntity_->addComponent<IngredientViewer>();
	ingPoolEntity_->addComponent<IngredientMotion>();

	//Componentes extra
	jute::jValue components = jsonLevel["IngredientsPool"]["components"];
	for (int c = 0; c < components.size(); ++c) { //Si tiene algun componente extra en ese nivel, se a�ade
		initializeComponent(components[c].as_string(), ingPoolEntity_);
	}
}


constexpr unsigned int str2int(const char* str, int h = 0)
{
	return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}


//La cadena (component) no puede superar 10 caracteres
void IngAdder::initializeComponent(const string& component, Entity* entity)
{
	switch (str2int(component.c_str()))
	{
	case str2int("AdvEffect"):
		break;
	default:
		break;
	}
}