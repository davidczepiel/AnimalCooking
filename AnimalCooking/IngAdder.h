#pragma once
#include <string>
#include "Entity.h"
#include "jute.h"
#include "Transform.h"
#include "TimerViewer.h"

class IngAdder
{
public:
	IngAdder(Entity* ing, jute::jValue& jsonLevel, jute::jValue& jsonGeneral, Transform* t1, Transform* t2, TimerViewer* tv);

private:

	Entity* ingPoolEntity_;
	jute::jValue& jsonLevel; // json con la informacion del nivel (pos, componentes extras particulares, etc...)
	jute::jValue& jsonGeneral; // json con las caracteristicas de los actores (size, velocidad, componentes genericos, etc...)

	TimerViewer* tv_;
	void initializeComponent(const string& component, Entity* entity);
};
