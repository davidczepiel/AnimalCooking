#include "MapLevelPool.h"

//MapLevelPool::MapLevelPool(size_t initialSize): Component(ecs::MapLevelPool)
//{
//	mapPool_.reserve(initialSize);
//}
//
//MapLevelPool::~MapLevelPool()
//{
//	for (MapLevel* ml : mapPool_) {
//		delete ml;
//	}
//}
//
//template<typename Ml, typename ...Targs>
//inline Ml* MapLevelPool::addMapLevel(Targs&& ...mArgs)
//{
//	assert(mapPool_.size() < mapPool_.capacity());
//	Ml* m(new C(std::forward<Targs>(mArgs)...));
//	mapPool_.emplace_back(m);
//	return m;
//}
//
//MapLevel* MapLevelPool::addMapLevel(MapLevel* m)
//{
//	assert(mapPool_.size() < mapPool_.capacity());
//	mapPool_.emplace_back(m);
//	return m;
//}

