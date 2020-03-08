#include "CookerPool.h"

CookerPool::CookerPool(size_t sizeIni): Component(ecs::CookerPool)
{
	cookers.reserve(sizeIni);
}

CookerPool::~CookerPool()
{
	for (Cooker* en : cookers) {
		delete en;
	}
}

void CookerPool::update()
{
	for (Cooker* en : cookers) {
		en->update();
	}
}

void CookerPool::draw()
{
	for (Cooker* en : cookers) {
		en->draw();
	}
}
