#include "MapLevelPool.h"

MapLevelPool::MapLevelPool(size_t initialSize): Component(ecs::MapLevelPool){
	mapPool_.reserve(initialSize);
}

MapLevelPool::~MapLevelPool()
{
	for (MapLevel* ml : mapPool_) {
		delete ml;
	}
}

void MapLevelPool::update()
{

}

