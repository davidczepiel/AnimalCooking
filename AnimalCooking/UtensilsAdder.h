#pragma once
#include "jute.h"
#include <string>
#include "Entity.h"
#include "Transport.h"
#include <array>

class UtensilsPool;
class UtensilsAdder
{
public:
    UtensilsAdder(Entity* utensilsPool, jute::jValue jsonLevel, jute::jValue jsonGeneral, std::array<Entity*, 2>& players);
private:

	void switchUten(const string& ing, UtensilsPool* utensilpool_, std::array<Entity*, 2>& player);
	void initializeComponent(const string& component, Entity* entity);

	Entity* utensilsPool;
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral;// json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	template<typename T>
	void makeUtensil(std::array<Entity*, 2>& player);
};

