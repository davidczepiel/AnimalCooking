#include "CookerPool.h"

CookerPool::CookerPool(size_t sizeIni): Component(ecs::CookerPool)
{
	pool_.reserve(sizeIni);
}

CookerPool::~CookerPool()
{
	for (Cooker* en : pool_) {
		delete en;
	}
}

void CookerPool::update()
{
	for (Cooker* en : pool_) {
		en->update();
	}
}

//void CookerPool::draw()
//{
//	for (Cooker* en : cookers) {
//		en->draw();
//	}
//}
