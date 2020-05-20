#include "MapLevelViewer.h"
#include "MapLevelPool.h"

MapLevelViewer::MapLevelViewer(): Component(ecs::MapLevelViewer) {
}

MapLevelViewer::~MapLevelViewer()
{
}

void MapLevelViewer::init()
{
	mapPool_ = GETCMP1_(MapLevelPool)->getMapPool();
}

void MapLevelViewer::update()
{
}

void MapLevelViewer::draw()
{
	for (MapLevel* ml : mapPool_) {
		
	}
}
