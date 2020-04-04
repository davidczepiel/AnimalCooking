#pragma once
#include <string>
#include "Entity.h"
#include "jute.h"

class IngAdder
{
public:
	IngAdder(Entity* ing, jute::jValue& jsonLevel, jute::jValue& jsonGeneral);

private:

	Entity* ingPoolEntity_;
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	template <typename T>
	void makeIngredient(int type, int n);
	void switchIng(const string& ing, int type, int n);
	void initializeComponent(const string& component, Entity* entity);
};

