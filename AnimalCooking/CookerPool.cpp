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