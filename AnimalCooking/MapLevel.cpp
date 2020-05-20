#include "MapLevel.h"

MapLevel::MapLevel(): 
	mapState_(MapLevelState::unselected),
	selectedText_(nullptr),
	unselectedText_(nullptr)
{

}

MapLevel::~MapLevel() {

}
