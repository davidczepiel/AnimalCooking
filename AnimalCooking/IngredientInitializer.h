#pragma once
#include <string>
#include "Entity.h"
#include "jute.h"
#include "GameControl.h"

class IngredientInitializer
{
public:

	IngredientInitializer(jute::jValue& jsonLevel, GameControl* gc);

private:
	Resources::IngredientType newIngType(const string& s);
};

