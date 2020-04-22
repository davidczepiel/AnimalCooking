#pragma once
#include <string>
#include "Entity.h"
#include "jute.h"
#include "GameControl.h"

class IngredientInitializer
{
public:

	IngredientInitializer(jute::jValue& jsonLevel,GameControl* gc);

private:
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
};

