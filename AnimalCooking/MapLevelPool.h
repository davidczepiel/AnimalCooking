#pragma once
#include "Component.h"
#include "Entity.h"
#include "MapLevel.h"

class MapLevelPool : public Component {
public:
	MapLevelPool(size_t initialSize = 5);
	 ~MapLevelPool();

	template<typename Ml, typename ...Targs>
	inline Ml* addMapLevel(Targs&& ...mArgs)
	{
		assert(mapPool_.size() < mapPool_.capacity());
		Ml* m(new Ml(std::forward<Targs>(mArgs)...));
		mapPool_.emplace_back(m);
		return m;
	}

	MapLevel* addMapLevel(MapLevel* m)
	{
		assert(mapPool_.size() < mapPool_.capacity());
		mapPool_.emplace_back(m);
		return m;
	}

	void update() override;
	vector<MapLevel*>& getMapPool() { return mapPool_; };

private:
	vector<MapLevel*> mapPool_;
};

