#include "Component.h"
#include "MapConfig.h"

class MapLevel: public Component{
public:
	MapLevel(levelInfo lvl);
	~MapLevel();

private:
	levelInfo info_;
};